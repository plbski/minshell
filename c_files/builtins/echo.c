/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/26 20:17:59 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

int	exec_echo(char *arg, char *nxt, int *found_flag, int *found_valid)
{
	int	is_flag;

	is_flag = 0;
	if (!*found_valid && arg[0] == '-' && only_chars(arg + 1, "n"))
	{
		if (!*found_flag)
			return (*found_flag = 1, 1);
		if (!*found_valid)
			return (1);
		is_flag = 1;
	}
	write(1, arg, ft_strlen(arg));
	if (nxt)
		write(1, " ", 1);
	if (!is_flag)
		*found_valid = 1;
	return (1);
}

int	echo(t_data *d, char *arg, char **flags, int direct)
{
	int	i;
	int	found_flag;
	int	found_valid_arg;

	(void)d;
	if (!arg && (!flags || !flags[0]))
		return (write(1, "\n", 1), FCT_OK);
	found_valid_arg = 0;
	found_flag = 0;
	if (arg && flags)
		exec_echo(arg, flags[0], &found_flag, &found_valid_arg);
	else
		exec_echo(arg, NULL, &found_flag, &found_valid_arg);
	i = -1;
	while (flags && flags[++i])
		exec_echo(flags[i], flags[i + 1], &found_flag, &found_valid_arg);
	if (!found_flag && !direct)
		write(1, "\n", 1);
	return (FCT_OK);
}
