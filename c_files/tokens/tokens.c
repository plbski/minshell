/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:33:06 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/17 23:20:30 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

t_token	*new_token(char *name, t_token *prv, t_tktype type, int parenth_order)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->next = NULL;
	token->pipe_out = NULL;
	token->prv = prv;
	if (prv)
		prv->next = token;
	token->par = parenth_order;
	token->name = name;
	token->type = type;
	token->red_arg = NULL;
	token->redir = NULL;
	token->subsh_out = NULL;
	token->nxt_eval = NULL;
	token->is_redir = (type == tk_red_app || type == tk_red_in || \
		type == tk_red_out || type == tk_hered);
	return (token);
}

t_token	*token_first(t_token *lst)
{
	t_token	*first;

	if (!lst)
		return (NULL);
	if (!lst->prv)
		return (lst);
	first = lst;
	while (first->prv)
		first = first->prv;
	return (first);
}

t_token	*get_token(t_token *lst, char *name)
{
	t_token	*first;

	if (!lst || !name)
		return (NULL);
	first = token_first(lst);
	while (first)
	{
		if (first->name && same_str(first->name, name))
			return (first);
		first = first->next;
	}
	return (NULL);
}

void	clear_tokens(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	token = token_first(token);
	while (token)
	{
		tmp = token;
		token = token->next;
		if (tmp->name)
			free(tmp->name);
		free(tmp);
	}
}

void	remove_token(t_token *token)
{
	if (!token)
		return ;
	if (token->prv)
		token->prv->next = token->next;
	if (token->next)
		token->next->prv = token->prv;
	if (token->name)
		free(token->name);
	free(token);
}
