/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:41:18 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/11 13:05:25 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	custom_exit(t_data *data, char *error_msg, char **flags, int status)
{
	int	exit_status;

	exit_status = status;
	write_history(data->history_wd);
	if (status != EXIT_CHILD && (!error_msg || !cmp_str(error_msg, "null")))
		ft_dprintf(2, "exit\n");
	if (flags && flags[0])
		return (ft_dprintf(2, "msh: exit: too many arguments\n"), 0);
	if (error_msg && !cmp_str(error_msg, "null"))
	{
		if (status == EXIT_SUCCESS)
		{
			if (!is_all_digit(error_msg))
			{
				ft_dprintf(2, "msh: exit: %s: numeric \
argument required\n", error_msg);
				free_data(data);
				exit(EXIT_FAILURE);
			}
			exit_status = ft_atoi(error_msg);
		}
		else
			ft_dprintf(2, "Error: %s\n", error_msg);
	}
	return (free_data(data), exit(exit_status), FCT_FAIL);
}
