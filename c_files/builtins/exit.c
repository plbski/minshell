/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:41:18 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/30 20:40:27 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	is_all_digit(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

int	custom_exit(t_data *data, char *error_msg, char **flags, int status)
{
	int	exit_status;

	exit_status = status;
	write_history(data->history_wd);
	printf("exit\n");
	if (flags && flags[0])
		return (printf("msh: exit: too many arguments\n"), 0);
	fflush(stdout);
	fflush(stderr);
	if (error_msg)
	{
		if (status == EXIT_SUCCESS)
		{
			if (!is_all_digit(error_msg))
			{
				printf("msh: exit: %s: numeric argument required\n", error_msg);
				free_data(data);
				exit(EXIT_FAILURE);
			}
			exit_status = ft_atoi(error_msg);
		}
		else
			printf("Error: %s\n", error_msg);
	}
	return (free_data(data), exit(exit_status), FCT_FAIL);
}
