/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:41:18 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/21 17:08:10 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	free_data(t_data *data)
{
	int	free_count;

	free_count = 0;
	dblst_clear(&data->env, free);
	if (data->cwd)
		free_count += (free(data->cwd), 1);
	if (data->prev_cwd)
		free_count += (free(data->prev_cwd), 1);
	if (data->doc_wd)
		free_count += (free(data->doc_wd), 1);
	if (data->start_wd)
		free_count += (free(data->start_wd), 1);
	printf("freed %d items.\n", free_count);
	return (free_count);
}

void	custom_exit(t_data *data, int status)
{
	(void)status;
	free_data(data);
	fflush(stdout);
	fflush(stderr);
	write_animated_txt(END_ANIM_TEXT, 0, 0);
	exit(0);
}
