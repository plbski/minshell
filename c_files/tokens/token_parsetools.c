/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsetools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 22:27:52 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/27 10:00:18 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

int	requires_arg(t_token *node)
{
	return (node->type == tk_red_app || node->type == tk_red_in || \
	node->type == tk_red_out || node->type == tk_pipe || \
	node->type == tk_logical || node->type == tk_hered);
}

t_token	*get_next_redir(t_token *tok)
{
	t_token	*node;

	if (!tok)
		return (NULL);
	if (tok->is_rd && !tok->prv && tok->next && \
			tok->next->next && tok->next->next->is_rd)
		return (tok->next->next);
	node = tok->next;
	while (node)
	{
		if (node->type != tk_arg)
			break ;
		node = node->next;
	}
	if (node && node->is_rd)
		return (node);
	return (NULL);
}

void	set_redir_arg(t_token *tok)
{
	t_token	*next_redir;

	if (tok->type != tk_cmd && !tok->is_rd)
		return ;
	next_redir = get_next_redir(tok);
	if (!next_redir || next_redir->par != tok->par)
		return ;
	tok->redir = next_redir;
	tok->red_arg = tok->redir->next;
}

void	set_redir_redir(t_token *tok)
{
	while (tok)
	{
		if (tok->is_rd && (!tok->prv || tok->prv->type != tk_cmd) && \
				tok->next && tok->next->next && tok->next->next->type == tk_cmd)
		{
			swap_tokens(tok->next, tok);
			swap_tokens(tok->next->next, tok);
			continue ;
		}
		tok->redir = NULL;
		if (tok->is_rd)
			set_redir_arg(tok);
		tok = tok->next;
	}
}

int	set_heredocs(t_data *d, t_token *tok)
{
	while (tok)
	{
		if (tok->type == tk_hered && !set_heredoc(d, tok))
			return (0);
		tok = tok->next;
	}
	return (1);
}
