/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:54:32 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/26 17:48:13 by giuliovalen      ###   ########.fr       */
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
	set_key_value(data, data->env_list, "OLDPWD", data->prev_cwd);
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
	data->history_wd = ft_strjoin(working_dir_buff, "/.history.txt");
	read_history(data->history_wd);
	return (1);
}

int	init_cwd(t_data *data)
{
	init_data_directories(data);
	update_cwd(data);
	return (1);
}

void	init_shlvl(t_data *data)
{
	char	*lvl;

	data->shlvl = 1;
	lvl = get_env_value(data, "SHLVL");
	if (!lvl)
		return ;
	data->shlvl = ft_atoi(lvl);
	free(lvl);
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
	data->environ = NULL;
	data->env_list = NULL;
	data->tmp_list = NULL;
	update_env_list(data, env);
	data->environ = list_to_arr(data->env_list);
	update_env_variables(data);
	init_cwd(data);
	init_shlvl(data);
	init_builtins_data(data);
}
