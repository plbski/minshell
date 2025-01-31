/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:33:06 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/31 19:48:35 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

t_token	*new_token(char *name, t_token *prv, t_toktype type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->next = NULL;
	token->prv = prv;
	if (prv)
		prv->next = token;
	token->name = name;
	token->type = type;
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
		if (first->name && cmp_str(first->name, name))
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
