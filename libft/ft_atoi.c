/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:38:47 by gvalente          #+#    #+#             */
/*   Updated: 2024/10/03 11:41:34 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static void	set_variables(int *res, int *i, int *is_minus)
{
	*res = 0;
	*i = 0;
	*is_minus = 1;
}

int	ft_atoi(const char *str)
{
	int	res;
	int	i;
	int	is_minus;

	set_variables(&res, &i, &is_minus);
	while (ft_isspace(str[i]))
		i++;
	if (!str || (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+'))
		return (0);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			is_minus = -1;
		i++;
	}
	if (!str[i] || !ft_isdigit(str[i]))
		return (0);
	while (str[i] && ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	res *= is_minus;
	return (res);
}
