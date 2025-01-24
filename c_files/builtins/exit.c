/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:41:18 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/24 13:48:11 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	custom_exit(t_data *data, char *arg, char *flags, int status)
{
	(void)arg;
	(void)flags;
	(void)status;
	write_history(data->history_wd);
	free_data(data);
	fflush(stdout);
	fflush(stderr);
	write_animated_txt(END_ANIM_TEXT, 0, 0);
	exit(0);
	return (1);
}
