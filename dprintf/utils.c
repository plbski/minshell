/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:30:10 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/04 17:15:36 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	d_putchar(int fd, char c)
{
	return ((int)write(fd, &c, 1));
}

int	d_putstr(int fd, char *str)
{
	int	len;

	if (str == NULL)
		return (d_putstr(fd, "(null)"));
	len = 0;
	while (str[len])
		if (d_putchar(fd, str[len++]) == -1)
			return (-1);
	return (len);
}

int	d_strlen(const char *src)
{
	int	i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

char	*d_strdup(const char	*s1)
{
	char	*dst;
	int		i;
	int		len;

	len = d_strlen(s1);
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	d_putptr(int fd, void *ptr)
{
	uintptr_t	address;
	char		buffer[16];
	int			i;
	int			count;

	if (!ptr)
		return (d_putstr(fd, "0x0"));
	address = (uintptr_t)ptr;
	count = d_putstr(fd, "0x");
	if (count == -1)
		return (-1);
	i = 0;
	while (address)
	{
		buffer[i++] = HEXDIGITS_MIN[address % 16];
		address /= 16;
	}
	while (i--)
	{
		if (d_putchar(fd, buffer[i]) == -1)
			return (-1);
		count++;
	}
	return (count);
}
