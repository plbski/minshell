/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:54:32 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/07 14:31:15 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	*custom_get_cwd(t_data *d)
{
	char	*working_dir_buff;

	working_dir_buff = malloc(MAX_DIR_LEN);
	if (!working_dir_buff)
		custom_exit(d, "alloc for cwd", NULL, EXIT_FAILURE);
	if (!getcwd(working_dir_buff, MAX_DIR_LEN))
	{
		free(working_dir_buff);
		custom_exit(d, "alloc for cwd", NULL, EXIT_FAILURE);
	}
	return (working_dir_buff);
}

int	update_cwd(t_data *data)
{
	char	*working_dir_buff;

	working_dir_buff = custom_get_cwd(data);
	if (data->cwd)
	{
		if (data->prev_cwd)
			free(data->prev_cwd);
		data->prev_cwd = ms_strdup(data, data->cwd);
		free(data->cwd);
	}
	set_key_value(data, data->env_list, "OLDPWD", data->prev_cwd);
	data->cwd = working_dir_buff;
	return (1);
}

static int	init_data_directories(t_data *data)
{
	char	*working_dir_buff;

	working_dir_buff = custom_get_cwd(data);
	data->start_wd = working_dir_buff;
	data->man_wd = ft_strjoin(working_dir_buff, "/man/");
	data->history_wd = ft_strjoin(working_dir_buff, "/.history.txt");
	read_history(data->history_wd);
	return (1);
}

static void	init_shlvl(t_data *data)
{
	char	*lvl;

	lvl = get_env_value(data, data->env_list, "SHLVL");
	if (lvl)
	{
		data->shlvl = ft_atoi(lvl) + 1;
		free(lvl);
	}
	else
	{
		add_to_list(data, data->env_list, "SHLVL=1");
		data->shlvl = 1;
		update_environ(data);
	}
}

void	init_data(t_data *data, char **env)
{
	data->cwd = NULL;
	data->prev_cwd = NULL;
	data->start_wd = NULL;
	data->home_wd = NULL;
	data->logname = NULL;
	data->man_wd = NULL;
	data->environ = NULL;
	data->env_list = NULL;
	data->tmp_list = NULL;
	data->pipefd = -1;
	data->fd = -1;
	g_quit_in_heredoc = 0;
	data->last_cmd_status = FCT_FAIL;
	data->last_exit_status = 0;
	init_env_list(data, env);
	data->environ = list_to_arr(data->env_list);
	update_env_variables(data);
	init_data_directories(data);
	update_cwd(data);
	init_shlvl(data);
	init_builtins_data(data);
}
