/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:29:00 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/16 15:24:20 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

t_token	*get_next_token(t_token *token, t_tktype type, int stops_at_same)
{
	t_tktype	same_type;

	same_type = token->type;
	token = token->next;
	while (token)
	{
		if (token->type == type)
			return (token);
		if (stops_at_same && token->type == same_type)
			return (NULL);
		token = token->next;
	}
	return (NULL);
}

void	link_token_pipes(t_token *tokens)
{
	t_token	*node;
	t_token	*output;

	node = token_first(tokens);
	while (node)
	{
		if (node->type == tk_command)
		{
			output = get_next_token(node, tk_pipe, 1);
			if (output)
			{
				node->pipe_out = output->next;
				if (output->next && output->next->is_redir)
				{
					if (output->next->next)
						output->next->next->type = tk_argument;
				}
			}
		}
		node = node->next;
	}
}

t_token	*get_last_arg(t_token *cmd)
{
	t_token	*next;

	if (!cmd || !cmd->next)
		return (NULL);
	next = cmd->next;
	while (next)
	{
		if (!next->next || next->next->type == tk_logical || \
			next->next->type == tk_pipe || next->next->is_redir)
			return (next);
		next = next->next;
	}
	return (NULL);
}

void	set_node_redir(t_token *cmd)
{
	cmd->redir = get_next_redir(cmd);
	if (!cmd->redir)
		return ;
	if (cmd->redir->type != tk_red_in)
		cmd->red_arg = cmd->redir->next;
	else
		cmd->red_arg = get_last_arg(cmd);
}
