/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:13 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/26 14:49:14 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lists.h"

static t_dblist	*get_db_list(t_dblist *lst, void *(*f)(void *), \
	void (*del)(void *))
{
	t_dblist	*new_node;
	t_dblist	*new_list;
	void		*new_content;

	new_list = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		if (!new_content)
		{
			dblst_clear(&new_list, del);
			return (NULL);
		}
		new_node = dblst_new(new_content);
		if (!new_node)
		{
			del(new_content);
			dblst_clear(&new_list, del);
			return (NULL);
		}
		dblst_add_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

t_dblist	*dblst_map(t_dblist *lst, void *(*f)(void *), \
	void (*del)(void *))
{
	if (!lst || !f)
		return (NULL);
	return (get_db_list(lst, f, del));
}

void	dblst_iter(t_dblist *lst, void (*f)(void *))
{
	t_dblist	*start;

	if (!lst || !f)
		return ;
	lst = dblst_first(lst);
	if (!lst)
		return ;
	start = lst;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
		if (lst == start)
			break ;
	}
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
