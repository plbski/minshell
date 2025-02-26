/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:25:15 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/17 23:20:31 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../msh.h"

int	same_str(const char *a, const char *b)
{
	int	len_a;
	int	len_b;
	int	i;

	if (!a || !b)
		return (0);
	len_a = ft_strlen(a);
	len_b = ft_strlen(b);
	if (len_a != len_b)
		return (0);
	i = -1;
	while (++i < len_a)
	{
		if (a[i] != b[i])
			return (0);
	}
	return (1);
}

int	char_in_str(char c, const char *txt)
{
	int	i;

	i = -1;
	while (txt[++i])
	{
		if (txt[i] == c)
			return (1);
	}
	return (0);
}

int	chr_amnt(const char *str, char c)
{
	int	i;
	int	occurence;

	if (!str)
		return (0);
	occurence = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			occurence++;
	}
	return (occurence);
}

int	get_arr_len(void **arr)
{
	int	len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}
