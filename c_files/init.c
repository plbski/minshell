/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:54:32 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/21 21:26:48 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	update_cwd(t_data *data)
{
	char	*working_dir_buff;

	working_dir_buff = malloc(MAX_DIR_LEN);
	if (!working_dir_buff)
		return (data->status = quitting, 0);
	if (!getcwd(working_dir_buff, MAX_DIR_LEN))
		return (free(working_dir_buff), data->status = quitting, 0);
	if (data->cwd)
	{
		if (data->prev_cwd)
			free(data->prev_cwd);
		data->prev_cwd = ft_strdup(data->cwd);
		free(data->cwd);
	}
	else
	{
		if (data->prev_cwd)
			free(data->prev_cwd);
		data->prev_cwd = ft_strdup(working_dir_buff);
	}
	data->cwd = working_dir_buff;
	return (1);
}

int	init_data_directories(t_data *data)
{
	char	*working_dir_buff;

	working_dir_buff = malloc(MAX_DIR_LEN);
	if (!working_dir_buff)
		return (data->status = quitting, 0);
	if (!getcwd(working_dir_buff, MAX_DIR_LEN))
		return (free(working_dir_buff), data->status = quitting, 0);
	data->start_wd = working_dir_buff;
	data->doc_wd = ft_strjoin(working_dir_buff, "/doc/");
	return (1);
}

int	init_cwd(t_data *data)
{
	init_data_directories(data);
	update_cwd(data);
	return (1);
}

void	init_data(t_data *data, char **env)
{
	data->status = running;
	data->cwd = NULL;
	data->prev_cwd = NULL;
	data->start_wd = NULL;
	data->home_wd = NULL;
	data->logname = NULL;
	data->doc_wd = NULL;
	data->environ = env;
	data->env_list = NULL;
	init_env_variables(data);
	update_env_variables(data);
	init_cwd(data);
}
