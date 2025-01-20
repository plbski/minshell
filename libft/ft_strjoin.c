/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:16:05 by gvalente          #+#    #+#             */
/*   Updated: 2024/10/03 18:10:51 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		u;
	char	*joined;

	joined = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined)
		return (NULL);
	i = 0;
	u = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	while (s2[u])
	{
		joined[i + u] = s2[u];
		u++;
	}
	joined[i + u] = '\0';
	return (joined);
}
