/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:09:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/12 12:58:17 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lists.h"

int	dblst_size(t_dblist *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

t_dblist	*dblst_first(t_dblist *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}

t_dblist	*dblst_last(t_dblist *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_dblist	*get_dblst_at_key(t_dblist *lst, char *key)
{
	t_dblist	*start;
	char		*content;
	int			j;

	if (!lst || !key)
		return (NULL);
	lst = dblst_first(lst);
	if (!lst)
		return (NULL);
	start = lst;
	while (lst)
	{
		content = (char *)lst->content;
		if (content)
		{
			j = 0;
			while (content[j] == key[j] && content[j] != '=')
				j++;
			if (!content[j] || content[j] == '=')
				return (lst);
		}
		lst = lst->next;
		if (lst == start)
			break ;
	}
	return (NULL);
}
