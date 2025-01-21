/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:23:03 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/21 15:20:34 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lists.h"

void	dblst_clear(t_dblist **lst, void (*del)(void *))
{
	t_dblist	*cur;
	t_dblist	*tmp;

	if (!lst || !*lst)
		return ;
	cur = *lst;
	while (cur)
	{
		tmp = cur->next;
		del(cur->content);
		free(cur);
		cur = tmp;
	}
	*lst = NULL;
}

void	dblst_delone(t_dblist *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (lst->content)
		del(lst->content);
	if (lst->next)
		lst->next->prev = lst->prev;
	if (lst->prev)
		lst->prev->next = lst->next;
	free(lst);
}
