/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:30:10 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/13 21:41:21 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	return ((int)write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	len;

	if (str == NULL)
		return (ft_putstr("(null)"));
	len = 0;
	while (str[len])
		if (ft_putchar(str[len++]) == -1)
			return (-1);
	return (len);
}

int	ft_putptr(void *ptr)
{
	uintptr_t	address;
	char		buffer[16];
	int			i;
	int			count;

	if (!ptr)
		return (ft_putstr("0x0"));
	address = (uintptr_t)ptr;
	count = ft_putstr("0x");
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
		if (ft_putchar(buffer[i]) == -1)
			return (-1);
		count++;
	}
	return (count);
}
