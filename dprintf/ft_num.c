/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:16:44 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/04 17:06:12 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>

static int	d_get_converted_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*d_handle_min(int n)
{
	int		len;
	char	*str;

	if (n == INT_MIN)
		return (d_strdup("-2147483648"));
	len = d_get_converted_len(n);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[0] = '-';
	n = -n;
	str[len] = '\0';
	while (n)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

char	*d_itoa(int n)
{
	char	*res;
	int		len;

	if (n == 0)
		return (d_strdup("0"));
	if (n < 0)
		return (d_handle_min(n));
	len = d_get_converted_len(n);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	while (n)
	{
		res[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (res);
}

static int	d_get_unsigned_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*d_utoa(unsigned int n)
{
	char	*res;
	int		len;

	if (n == 0)
		return (d_strdup("0"));
	len = d_get_unsigned_len(n);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	while (n)
	{
		res[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (res);
}
