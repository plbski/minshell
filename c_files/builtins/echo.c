/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/31 17:23:07 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	exec_echo(char *str, char *next_str)
{
	if (cmp_str(str, "-n"))
		return (1);
	write(1, str, ft_strlen(str));
	if (next_str && !cmp_str(next_str, "-n"))
		write(1, " ", 1);
	return (0);
}

int	echo(t_data *d, char *arg, char **flags, int status __attribute__((unused)))
{
	int	i;
	int	n_flag;

	(void)d;
	n_flag = 0;
	if (!arg)
	{
		write(1, "\n", 1);
		return (FCT_SUCCESS);
	}
	n_flag = exec_echo(arg, flags[0]);
	i = -1;
	while (flags && flags[++i])
	{
		if (exec_echo(flags[i], flags[i + 1]))
			n_flag = 1;
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (FCT_SUCCESS);
}
