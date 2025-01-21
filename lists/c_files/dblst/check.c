/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:09:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/21 17:44:49 by giuliovalen      ###   ########.fr       */
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

t_dblist	*get_dblst_at_key(t_dblist *lst, char *prefix)
{
	char	*content;
	int		j;

	if (!prefix)
		return (NULL);
	lst = dblst_first(lst);
	while (lst->next && lst->next->content)
	{
		content = (char *)lst->content;
		j = 0;
		while (content[j] == prefix[j])
			j++;
		if (!prefix[j])
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
