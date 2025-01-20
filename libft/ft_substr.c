/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:15:45 by gvalente          #+#    #+#             */
/*   Updated: 2024/10/04 16:10:41 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*return_empty(void)
{
	char	*new_str;

	new_str = malloc(1);
	if (!new_str)
		return (NULL);
	new_str[0] = '\0';
	return (new_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*new_str;
	size_t		i;
	size_t		s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (return_empty());
	if (len > s_len - start)
		len = s_len - start;
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	new_str[0] = '\0';
	if (start >= s_len)
		return (new_str);
	i = 0;
	while (i < len && s[start + i])
	{
		new_str[i] = s[start + i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
