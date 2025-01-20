/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:39:37 by gvalente          #+#    #+#             */
/*   Updated: 2024/10/03 13:08:27 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char		*last_occurrence;
	unsigned char	ch;

	last_occurrence = NULL;
	ch = (unsigned char)c;
	while (*s)
	{
		if (*s == ch)
			last_occurrence = s;
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return ((char *)last_occurrence);
}
