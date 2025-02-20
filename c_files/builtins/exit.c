/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:41:18 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/20 21:05:50 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static int	free_and_quit(t_data *d, int status)
{
	int			freed_len;

	freed_len = free_data(d);
	if (d->debug_mode)
	{
		if (d->fork_child)
			ft_dprintf(2, "%s[%d]fork child ", d->fork_child, MAGENTA);
		ft_dprintf(2, "[freed %d] exit with code %d\n", freed_len, status);
		if (d->fork_child)
			ft_dprintf(2, "%s", RESET);
	}
	exit(status);
	ft_dprintf(2, "exit failed\n");
	return (FCT_FAIL);
}

static int	exit_unvalid_argument(t_data *d, char *error_msg)
{
	ft_dprintf(2, "msh: exit: %s: numeric argument required\n", error_msg);
	return (free_and_quit(d, 255));
}

static int	is_valid_exit_argument(char *arg, int *ret_val, int i)
{
	int		found_num;
	char	sign;

	if (!arg[0] || only_space(arg))
		return (0);
	found_num = -1;
	sign = '\0';
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '-' || arg[i] == '+')
		{
			if (found_num != -1 || sign)
				return (0);
			sign = arg[i];
		}
		else if (ft_isdigit(arg[i]) && found_num == -1)
			found_num = i;
		else if (!ft_isdigit(arg[i]) && (arg[i] != ' ' && arg[i] != '\t'))
			return (0);
	}
	if (found_num == -1)
		return (0);
	*ret_val = ft_atoi(arg + found_num) * (1 - ((sign == '-') * 2));
	return (1);
}

int	custom_exit(t_data *d, char *msg, char **flags, int st)
{
	int			exit_status;

	exit_status = st;
	if (st == EXIT_SUCCESS && !msg)
		exit_status = d->last_exit;
	write_history(d->history_wd);
	if (!d->fork_child && st != EXIT_CHILD && (!msg || !same_str(msg, "null")))
		ft_dprintf(2, "exit\n");
	if (flags && flags[0])
		return (ft_dprintf(2, "msh: exit: too many arguments\n"), 0);
	if (msg && !same_str(msg, "null"))
	{
		if (st == EXIT_SUCCESS)
		{
			if (!is_valid_exit_argument(msg, &exit_status, -1))
				return (exit_unvalid_argument(d, msg));
		}
		else
			ft_dprintf(2, "Error: %s\n", msg);
	}
	free_and_quit(d, exit_status);
	return (free_and_quit(d, exit_status));
}
