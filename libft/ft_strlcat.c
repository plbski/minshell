/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:39:25 by gvalente          #+#    #+#             */
/*   Updated: 2024/10/02 20:10:43 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *d, const char *s, size_t	sz)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;

	src_len = ft_strlen(s);
	dst_len = ft_strlen(d);
	if (sz <= dst_len)
		return (sz + src_len);
	i = 0;
	while (s[i] && dst_len + i < (sz - 1))
	{
		d[dst_len + i] = s[i];
		i++;
	}
	d[dst_len + i] = '\0';
	return (dst_len + src_len);
}
