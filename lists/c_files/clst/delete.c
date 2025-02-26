/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:23:03 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/21 16:27:47 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lists.h"

void	clst_clear(t_clst **lst, void (*del)(void *))
{
	t_clst	*cur;
	t_clst	*tmp;

	if (!lst || !*lst)
		return ;
	cur = *lst;
	if (cur->next == *lst)
	{
		del(cur->content);
		free(cur);
		*lst = NULL;
		return ;
	}
	tmp = cur->next;
	while (tmp != *lst)
	{
		cur = tmp;
		tmp = tmp->next;
		del(cur->content);
		free(cur);
	}
	del(cur->content);
	free(tmp);
	*lst = NULL;
}

void	clst_delone(t_clst *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (lst->next == lst)
	{
		del(lst->content);
		free(lst);
	}
	else
	{
		lst->prev->next = lst->next;
		lst->next->prev = lst->prev;
		del(lst->content);
		free(lst);
	}
}
