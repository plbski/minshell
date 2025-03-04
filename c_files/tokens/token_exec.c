/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:15:07 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/03/04 13:15:56 by giuliovalen      ###   ########.fr       */
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
			return (free_void_array((void ***)&flags), nxt);
		if (node->redir && node->redir->redir)
			nxt = handle_mult_redirs(d, node, arg, flags);
		else if (node->redir)
			nxt = handle_redir_cmd(d, node, arg, flags);
	}
	else
		d->last_exit = execute_command(d, node->name, arg, flags);
	if (d->debug_mode)
		show_exec_info(d, node, arg, flags);
	if (nxt && nxt->type == tk_arg)
		nxt = nxt->next;
	return (free_void_array((void ***)&flags), nxt);
}

static t_token	*skip_nodes(t_data *d, t_token *nod, int min_par)
{
	if (d->debug_mode)
		printf("%sSKIP lower par toks >%s%s", RED, RESET, nod->name);
	if (!nod->next || nod->next->type == tk_cmd)
		return (NULL);
	nod = nod->next;
	if (nod && nod->next)
	{
		if (d->debug_mode)
			printf("'%s%s%s' ", YELLOW, nod->name, RESET);
		nod = nod->next;
	}
	while (nod && (nod->par > min_par || \
			(nod->type != tk_cmd && nod->type != tk_logical)))
	{
		if (d->debug_mode)
			printf("'%s%s%s' ", YELLOW, nod->name, RESET);
		nod = nod->next;
	}
	if (d->debug_mode)
		printf("\n");
	if (nod && (nod->is_rd || nod->type == tk_pipe || \
			chr_amnt(nod->name, '=', 1)))
		return (nod->next);
	return (nod);
}

static t_token	*handle_logical_token(t_data *d, t_token *node)
{
	if ((same_str(node->name, "||") && d->last_exit != FCT_OK) || \
	(same_str(node->name, "&&") && d->last_exit == FCT_OK))
		return (node->next);
	return (skip_nodes(d, node, node->par));
}

static t_token	*handle_token(t_data *d, t_token *node)
{
	t_tktype	type;

	type = node->type;
	if (type == tk_logical)
		return (handle_logical_token(d, node));
	else if (chr_amnt(node->name, '=', 1))
		export(d, node->name, NULL, 1);
	else if (type == tk_cmd)
	{
		if (node->pipe_out)
			return (pipe_handler(d, node));
		return (handle_command_token(d, node, 1));
	}
	return (node->next);
}

void	iterate_tokens(t_data *d, t_token *node)
{
	t_token	*solved_subshell;

	while (node)
	{
		node = update_node_expansion(d, node);
		if (!node)
			break ;
		if (d->debug_mode)
			show_cmd_status(d, node);
		if (node->subsh_out)
		{
			solved_subshell = solve_subshell(d, node);
			if (solved_subshell)
			{
				node = solved_subshell;
				if (d->debug_mode)
				{
					show_token_info(d, node, "subsh", -1);
					printf("\n");
				}
			}
		}
		node = handle_token(d, node);
		d->var = 0;
	}
}
