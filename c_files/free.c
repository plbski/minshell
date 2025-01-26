/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:35:21 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/26 12:05:37 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	safe_free(void *line)
{
	if (line)
		free(line);
}

int	free_void_array(void ***item)
{
	int	free_count;

	if (item == NULL || *item == NULL)
		return (0);
	free_count = 0;
	while ((*item)[free_count] != NULL)
	{
		free((*item)[free_count]);
		(*item)[free_count] = NULL;
		free_count++;
	}
	free(*item);
	*item = NULL;
	return (free_count);
}

int	free_data(t_data *data)
{
	int	free_count;

	free_count = 0;
	dblst_clear(&data->env_list, free);
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
