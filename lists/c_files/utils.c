/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:22:55 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/21 16:29:39 by giuliovalen      ###   ########.fr       */
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
