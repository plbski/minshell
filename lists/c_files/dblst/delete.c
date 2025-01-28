/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:23:03 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/28 00:58:55 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lists.h"

void	dblst_clear(t_dblist **lst, void (*del)(void *))
{
	t_dblist	*cur;
	t_dblist	*tmp;

	if (!lst || !*lst)
		return ;
	cur = dblst_first(*lst);
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

void	print_content(void *content)
{
	if (content)
		printf("%s\n", (char *)content);
}

void	print_prefixed_content(void *content)
{
	if (content)
		printf("export %s\n", (char *)content);
}

void	dblst_print_list(t_dblist *lst, int has_prefix)
{
	if (lst)
	{
		if (has_prefix)
			dblst_iter(lst, print_prefixed_content);
		else
			dblst_iter(lst, print_content);
	}
}
