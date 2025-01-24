/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:41:18 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/24 17:33:19 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	custom_exit(t_data *data, char *error_msg, char *flags, int status)
{
	(void)flags;
	(void)status;
	write_history(data->history_wd);
	free_data(data);
	fflush(stdout);
	fflush(stderr);
	write_animated_txt(END_ANIM_TEXT, 0, 0);
	if (error_msg)
		printf("Error: %s\n", error_msg);
	exit(status);
	return (1);
}
