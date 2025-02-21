/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:29:00 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/21 17:21:01 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

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
		if (node->type == tk_cmd)
		{
			output = get_next_token(node, tk_pipe, 1);
			if (output)
			{
				if (output->par != tokens->par)
					break ;
				node->pipe_out = output->next;
				if (output->next && output->next->is_rd)
				{
					if (output->next->next)
						output->next->next->type = tk_arg;
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
			next->next->type == tk_pipe || next->next->is_rd)
			return (next);
		next = next->next;
	}
	return (NULL);
}

void	set_parenthesis_rdections(t_token *tok)
{
	t_token	*node;

	node = tok->next;
	while (node)
	{
		if (node->par < tok->par)
			break ;
		node = node->next;
	}
	if (node && node->is_rd)
		tok->redir = node;
}
