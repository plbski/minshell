/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:39:13 by gvalente          #+#    #+#             */
/*   Updated: 2024/10/04 15:26:27 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_pointer(unsigned char **p1, const unsigned char **p2)
{
	**p1 = **p2;
	(*p1)++;
	(*p2)++;
}

static void	set_pointer_up(unsigned char **p1, const unsigned char **p2)
{
	(*p1)--;
	(*p2)--;
	**p1 = **p2;
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*p1;
	const unsigned char	*p2;

	if (!dst && !src)
		return (NULL);
	p1 = (unsigned char *) dst;
	p2 = (const unsigned char *) src;
	if (p1 > p2 && p1 < p2 + len)
	{
		p1 += len;
		p2 += len;
		while (len--)
			set_pointer_up(&p1, &p2);
	}
	else
	{
		while (len--)
			set_pointer(&p1, &p2);
	}
	return (dst);
}
