/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:33:06 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/31 00:11:27 by giuliovalen      ###   ########.fr       */
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
	if (prv)
	{
		prv->next = token;		
		token->prv = prv;
	}
	token->name = name;
	token->type = type;
	return (token);
}

t_token	*token_first(t_token *lst)
{
	t_token	*first;

	first = lst;
	while (first->prv)
		first = first->prv;
	return (first);
}

t_token	*get_token(t_token *lst, char *name)
{
	t_token	*first;

	first = token_first(lst);
	if (!first)
		return (NULL);
	while (first->next)
	{
		if (is_same_string(first->name, name))
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
		if (tmp->name)
			free(tmp->name);
		token = token->next;
		free(tmp);
	}
}
