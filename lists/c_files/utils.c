/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:22:55 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/26 12:06:38 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lists.h"

char	*list_strdup(const char *str)
{
	size_t	len;
	char	*copy;
	size_t	i;

	if (!str)
		return (NULL);
	len = 0;
	while (str[len])
		len++;
	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	i = -1;
	while (++i < len)
		copy[i] = str[i];
	copy[len] = '\0';
	return (copy);
}

char	**list_to_arr(t_dblist *l)
{
	char	**list;
	int		list_size;
	int		i;

	if (!l)
		return (NULL);
	list_size = dblst_size(l);
	l = dblst_first(l);
	list = malloc(sizeof(char *) * (list_size + 1));
	if (!list)
		return (NULL);
	i = 0;
	while (l->next)
	{
		list[i++] = list_strdup(l->content);
		l = l->next;
	}
	list[i] = NULL;
	return (list);
}

int	list_strlen(char *content)
{
	int	i;

	if (!content)
		return (0);
	i = 0;
	while (content[i])
		i++;
	return (i);
}
