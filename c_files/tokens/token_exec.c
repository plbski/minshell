/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:15:07 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/19 19:09:07 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

t_token	*handle_command_token(t_data *d, t_token *node, int should_redir)
{
	t_token		*nxt;
	char		**flags;
	char		*arg;

	arg = NULL;
	flags = NULL;
	nxt = setup_args(d, &arg, node, &flags);
	if ((should_redir && node->redir) || d->heredocfd != -1)
	{
		if (!validate_redir(d, node->redir))
			return (NULL);
		if (node->redir)
			nxt = handle_redir_cmd(d, node, arg, flags);
		if (d->heredocfd != -1)
			nxt = consumate_heredoc(d, node, arg, flags);
	}
	else
		d->last_exit = execute_command(d, node->name, arg, flags);
	if (d->debug_mode)
		show_exec_info(d, node, arg, flags);
	if (nxt && nxt->type == tk_arg)
		nxt = nxt->next;
	return (free_void_array((void ***)&flags), nxt);
}

t_token	*skip_nodes(t_data *d, t_token *node)
{
	int		min_par;

	min_par = node->par;
	if (d->debug_mode)
		printf("%sskipping lower par tokens >%s ", RED, RESET);
	node = node->next;
	if (node && node->next)
	{
		if (d->debug_mode)
			printf("'%s%s%s' ", YELLOW, node->name, RESET);
		node = node->next;
	}
	while (node && (((node->type == tk_arg || node->is_redir) \
		|| node->par > min_par)))
	{
		if (d->debug_mode)
			printf("'%s%s%s' ", YELLOW, node->name, RESET);
		node = node->next;
	}
	if (d->debug_mode)
		printf("\n");
	if (node && node->is_redir)
		return (node->next);
	return (node);
}

static t_token	*handle_logical_token(t_data *d, t_token *node)
{
	if ((same_str(node->name, "||") && d->last_exit == FCT_OK) || \
	(same_str(node->name, "&&") && d->last_exit > 0))
		return (skip_nodes(d, node));
	return (node->next);
}

static t_token	*handle_token(t_data *d, t_token *node)
{
	t_tktype	type;

	type = node->type;
	if (type == tk_hered)
	{
		handle_redir_heredoc(d, node->next);
		return (node->next->next);
	}
	if (type == tk_logical)
		return (handle_logical_token(d, node));
	else if (type == tk_cmd)
	{
		if (node->pipe_out)
			return (pipe_handler(d, node));
		return (handle_command_token(d, node, 1));
	}
	if (type == tk_arg && chr_amnt(node->name, '=') == 1)
		export(d, node->name, NULL, 1);
	return (node->next);
}

void	iterate_tokens(t_data *d, t_token *node)
{
	t_token	*solved_subshell;

	while (node)
	{
		if (node->subsh_out)
		{
			solved_subshell = solve_subshell(d, node);
			if (solved_subshell)
			{
				node = solved_subshell;
				if (d->debug_mode)
				{
					show_token_info(d, node, "sbh node", 7);
					printf("\n");
				}
				continue ;
			}
		}
		update_node_expansion(d, node);
		if (!validate_token(d, &node))
			break ;
		if (d->debug_mode)
			show_cmd_status(d, node);
		node = handle_token(d, node);
	}
}
