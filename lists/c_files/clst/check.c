/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:09:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/21 15:23:37 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lists.h"

int	clst_size(t_clst *lst)
{
	t_clst	*cur;
	int		len;

	if (!lst)
		return (0);
	len = 1;
	cur = lst->next;
	while (cur != lst)
	{
		len++;
		cur = cur->next;
	}
	return (len);
}

t_clst	*clst_last(t_clst *lst)
{
	t_clst	*cur;

	if (!lst)
		return (NULL);
	cur = lst;
	while (cur->next != lst && cur->next)
		cur = cur->next;
	return (cur);
}
