/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:13 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/21 16:28:55 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lists.h"

t_clst	*clst_map(t_clst *lst, void *(*f)(void *), void (*del)(void *))
{
	t_clst	*new_list;
	t_clst	*cur;
	t_clst	*new_node;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	cur = lst;
	while (cur != NULL)
	{
		new_node = clst_new(f(cur->content));
		if (!new_node)
		{
			clst_clear(&new_list, del);
			return (NULL);
		}
		clst_add_back(&new_list, new_node);
		cur = cur->next;
		if (cur == lst)
			break ;
	}
	return (new_list);
}

void	clst_iter(t_clst *lst, void (*f)(void *))
{
	t_clst	*cur;

	cur = lst;
	if (!lst || !f)
		return ;
	while (cur != lst)
	{
		f(cur->content);
		cur = cur->next;
	}
}
