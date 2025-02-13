/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:35:21 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/13 06:14:16 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	safe_free(void *item)
{
	if (item)
	{
		free(item);
		return (1);
	}
	return (0);
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
	int	debug_output;

	debug_output = data->debug_mode;
	free_count = 0;
	free_count += dblst_size(data->env_list);
	dblst_clear(&data->env_list, free);
	free_count += dblst_size(data->tmp_list);
	dblst_clear(&data->tmp_list, free);
	free_count += dblst_size(data->tmp_list);
	dblst_clear(&data->var_list, free);
	free_count += free_void_array((void ***)&data->bltin_names);
	free_count += free_void_array((void ***)&data->types_names);
	free_count += free_void_array((void ***)&data->environ);
	free_count += safe_free(data->cwd);
	free_count += safe_free(data->prev_cwd);
	free_count += safe_free(data->start_wd);
	free_count += safe_free(data->man_wd);
	free_count += safe_free(data->history_wd);
	free_count += safe_free(data->logname);
	free_count += safe_free(data->home_wd);
	free_count += safe_free(data->prv_input);
	if (debug_output)
		printf("freed %d items.\n", free_count);
	return (free_count);
}
