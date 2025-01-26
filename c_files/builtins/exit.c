/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:41:18 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/26 12:38:53 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	custom_exit(t_data *data, char *error_msg, char **flags, int status)
{
	(void)flags;
	(void)status;
	write_history(data->history_wd);
	fflush(stdout);
	fflush(stderr);
	if (status == EXIT_FAILURE && error_msg)
		printf("Error: %s\n", error_msg);
	else
		write_anim_txt(data, END_ANIM_TEXT, 0, 0);
	free_data(data);
	exit(status);
	return (1);
}
