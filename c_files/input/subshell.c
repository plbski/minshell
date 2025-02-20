/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:35:57 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/18 13:07:49 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

t_token	*get_subsh_out(t_token *node)
{
	int	start_par;

	start_par = node->par;
	if (start_par <= 0)
		return (NULL);
	while (node)
	{
		if (node->par < start_par)
			return (node);
		node = node->next;
	}
	if (node && (node->is_redir || node->type == tk_pipe))
		return (node);
	return (NULL);
}

void	set_subshells(t_data *d, t_token *tokens)
{
	t_token	*node;
	int		sub_par;

	(void)d;
	node = token_first(tokens);
	while (node)
	{
		node->subsh_out = get_subsh_out(node);
		if (node->subsh_out)
		{
			sub_par = node->par;
			while (node->next && node->next->par == sub_par)
				node = node->next;
		}
		node = node->next;
	}
}
