/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:05:09 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/11 09:59:39 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

t_token	*handle_logical_token(t_data *d, t_token *node)
{
	int			min_par;

	if ((cmp_str(node->name, "||") && d->last_exit_st == FCT_SUCCESS) || \
	(cmp_str(node->name, "&&") && d->last_exit_st > 0))
	{
		min_par = node->par;
		node = node->next;
		if (node && node->next)
			node = node->next;
		while (node && ((node->type == tk_argument || node->par > min_par)))
		{
			if (d->debug_mode)
				printf("%sskipped %s%s\n", GREY, node->name, RESET);
			node = node->next;
		}
		return (node);
	}
	return (node->next);
}

t_token	*handle_token(t_data *d, t_token *node)
{
	t_tktype	type;

	type = node->type;
	if (type == tk_command || type == tk_exec)
	{
		if (node->pipe_out)
			return (handle_pipe(d, node));
		return (handle_command_token(d, node, 1));
	}
	if (type == tk_hered)
		return (handle_redir(d, node, node->next, node->type));
	if (type == tk_logical)
		return (handle_logical_token(d, node));
	if (type == tk_argument && chr_amnt(node->name, '=') == 1)
		export(d, node->name, NULL, 1);
	return (node->next);
}

int	exec_prompt(t_data *d, char *terminal_line)
{
	t_token	*tokens;
	t_token	*node;

	tokens = tokenize_string(d, terminal_line);
	if (!tokens)
		return (FCT_FAIL);
	node = token_first(tokens);
	d->last_cmd_status = -1;
	while (node)
	{
		update_node_expansion(d, node, 1);
		if (!validate_token(d, node))
			break ;
		if (d->debug_mode)
			show_cmd_status(d, node);
		node = handle_token(d, node);
	}
	clear_tokens(tokens);
	return (d->last_cmd_status);
}
