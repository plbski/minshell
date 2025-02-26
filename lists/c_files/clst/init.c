/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:07:37 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/21 15:34:15 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lists.h"

t_clst	*clst_new(void *content)
{
	t_clst	*new_node;

	new_node = malloc(sizeof(t_clst));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = new_node;
	new_node->prev = new_node;
	new_node->head = new_node;
	return (new_node);
}

void	clst_add_front(t_clst **lst, t_clst *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	new->prev = (*lst)->prev;
	(*lst)->prev->next = new;
	(*lst)->prev = new;
	(*lst)->head = new;
}

void	clst_add_back(t_clst **lst, t_clst *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	new->prev = (*lst)->prev;
	new->next = *lst;
	(*lst)->prev->next = new;
	(*lst)->prev = new;
}
