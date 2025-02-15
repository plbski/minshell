/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:54:32 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/14 21:45:20 by giuliovalen      ###   ########.fr       */
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
	data->man_wd = ms_strjoin(data, working_dir_buff, "/doc/");
	data->history_wd = ft_str_mega_join(working_dir_buff, \
		"/ressources/", ".history.txt", NULL);
	if (!data->history_wd)
		custom_exit(data, "alloc for history wd", NULL, EXIT_FAILURE);
	read_history(data->history_wd);
	data->heredoc_wd = ft_str_mega_join(working_dir_buff, \
		"/ressources/", ".heredoc.txt", NULL);
	if (!data->heredoc_wd)
		custom_exit(data, "alloc for heredoc_wd", NULL, EXIT_FAILURE);
	return (1);
}

void	init_base_stds(t_data *data)
{
	data->saved_stdin = -1;
	data->saved_stdout = -1;
	data->heredocfd = -1;
	data->fd = -1;
	data->base_stdin = dup(STDIN_FILENO);
	data->base_stdout = dup(STDOUT_FILENO);
	if (data->base_stdin == -1 || data->base_stdout == -1)
		custom_exit(data, "failed to save stds", NULL, EXIT_FAILURE);
}

void	init_data(t_data *data, char **env)
{
	init_base_stds(data);
	data->cwd = NULL;
	data->prev_cwd = NULL;
	data->start_wd = NULL;
	data->home_wd = NULL;
	data->logname = NULL;
	data->man_wd = NULL;
	data->environ = NULL;
	data->env_list = NULL;
	data->tmp_list = NULL;
	data->var_list = NULL;
	data->prv_input = NULL;
	g_quit_in_heredoc = 0;
	data->last_cmd_status = FCT_FAIL;
	data->last_exit_st = 0;
	init_env_list(data, env);
	data->environ = list_to_arr(data->env_list);
	update_env_variables(data);
	init_data_directories(data);
	update_cwd(data);
	init_builtins_data(data);
	export_usefull_var(data);
}
