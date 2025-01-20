/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:16:44 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/13 21:04:32 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

// static int	ft_get_converted_len(int n)
// {
// 	int	len;

// 	len = 0;
// 	if (n <= 0)
// 		len++;
// 	while (n)
// 	{
// 		n /= 10;
// 		len++;
// 	}
// 	return (len);
// }

// static char	*ft_handle_min(int n)
// {
// 	int		len;
// 	char	*str;

// 	if (n == INT_MIN)
// 		return (ft_strdup("-2147483648"));
// 	len = ft_get_converted_len(n);
// 	str = malloc(len + 1);
// 	if (!str)
// 		return (NULL);
// 	str[0] = '-';
// 	n = -n;
// 	str[len] = '\0';
// 	while (n)
// 	{
// 		str[--len] = (n % 10) + '0';
// 		n /= 10;
// 	}
// 	return (str);
// }

static int	ft_get_unsigned_len(unsigned int n)
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

char	*ft_utoa(unsigned int n)
{
	char	*res;
	int		len;

	if (n == 0)
		return (ft_strdup("0"));
	len = ft_get_unsigned_len(n);
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
