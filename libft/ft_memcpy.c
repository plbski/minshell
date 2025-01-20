/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:39:11 by gvalente          #+#    #+#             */
/*   Updated: 2024/10/03 11:34:34 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*p1;
	const unsigned char	*p2;

	if (!dst && !src)
		return (NULL);
	if (n <= 0)
		return (dst);
	p1 = (unsigned char *)dst;
	p2 = (unsigned char *)src;
	while (n--)
	{
		*p1 = *p2;
		p1++;
		p2++;
	}
	return (dst);
}
