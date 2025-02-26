/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:35:21 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/26 18:09:40 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../msh.h"

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

void	close_stds(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (data->base_stds[i] != -1)
		{
			close(data->base_stds[i]);
			data->base_stds[i] = -1;
		}
		if (data->saved_stds[i] != -1)
		{
			close(data->saved_stds[i]);
			data->saved_stds[i] = -1;
		}
	}
	if (data->heredocfd != -1)
		close(data->heredocfd);
}

int	free_data(t_data *data)
{
	int	free_count;

	free_count = 0;
	free_count += dblst_size(data->env_list);
	dblst_clear(&data->env_list, free);
	free_count += dblst_size(data->var_list);
	dblst_clear(&data->var_list, free);
	free_count += free_void_array((void ***)&data->bltin_names);
	free_count += free_void_array((void ***)&data->types_names);
	free_count += free_void_array((void ***)&data->environ);
	free_count += safe_free(data->cwd);
	free_count += safe_free(data->prev_cwd);
	free_count += safe_free(data->msh_wd);
	free_count += safe_free(data->man_wd);
	free_count += safe_free(data->heredoc_wd);
	free_count += safe_free(data->history_wd);
	free_count += safe_free(data->logname);
	free_count += safe_free(data->start_wd);
	free_count += safe_free(data->prompt_msg);
	free_count += safe_free(data->home_wd);
	free_count += safe_free(data->prv_input);
	clear_tokens(data->input_tokens);
	data->input_tokens = NULL;
	return (close_stds(data), free_count);
}
