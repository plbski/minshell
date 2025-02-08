/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/07 23:15:56 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static void	exec_echo(char *str, char *next_str)
{
	write(1, str, ft_strlen(str));
	if (next_str)
		write(1, " ", 1);
}

int	echo(t_data *d, char *arg, char **flags, int status __attribute__((unused)))
{
	int	i;
	int	n_flag;

	(void)d;
	if (!arg)
	{
		write(1, "\n", 1);
		return (FCT_SUCCESS);
	}
	n_flag = 0;
	if (arg[0] == '-' && arg[1] == 'n')
		n_flag = 1;
	else
		exec_echo(arg, flags[0]);
	i = -1;
	while (flags && flags[++i])
		exec_echo(flags[i], flags[i + 1]);
	if (!n_flag)
		write(1, "\n", 1);
	return (FCT_SUCCESS);
}
