/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 22:27:52 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/21 19:54:44 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

int	requires_arg(t_token *node)
{
	return (node->type == tk_red_app || node->type == tk_red_in || \
	node->type == tk_red_out || node->type == tk_pipe || \
	node->type == tk_logical || node->type == tk_hered);
}

int	is_valid_identifier(char *arg)
{
	int	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 0;
	while (arg[++i])
	{
		if (!ft_isalpha(arg[i]) && !ft_isdigit(arg[i]) && arg[i] != '_')
			return (0);
	}
	return (1);
}

t_token	*get_next_redir(t_token *d)
{
	t_token	*node;

	if (!d)
		return (NULL);
	node = d->next;
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

void	reorder_misplaced_redirs(t_data *d, t_token *start)
{
	t_token	*tk;

	if (d->debug_mode)
		show_tokens_info(d, start, "bef_swap", -1);
	tk = start;
	while (tk)
	{
		if (tk->is_rd && tk->type != tk_hered && tk->next && \
			(!tk->prv || tk->prv->type != tk_cmd) && \
			(tk->next->type == tk_cmd || tk->next->type == tk_arg))
			swap_redir_cmd(d, tk);
		tk = tk->next;
	}
}

void	set_redir_args(t_token *tok)
{
	t_token	*next_redir;

	while (tok)
	{
		tok->redir = NULL;
		if (tok->type == tk_cmd || tok->is_rd)
		{
			next_redir = get_next_redir(tok);
			if (!next_redir || next_redir->par != tok->par)
			{
				tok = tok->next;
				continue ;
			}
			tok->redir = next_redir;
			tok->red_arg = tok->redir->next;
		}
		tok = tok->next;
	}
}
