/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:54:32 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/19 22:47:14 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

char	*custom_get_cwd(t_data *d)
{
	char	*working_dir_buff;

	working_dir_buff = malloc(999);
	if (!working_dir_buff)
		custom_exit(d, "alloc for cwd", NULL, EXIT_FAILURE);
	if (!getcwd(working_dir_buff, 999))
	{
		free(working_dir_buff);
		custom_exit(d, "alloc for cwd", NULL, EXIT_FAILURE);
	}
	return (working_dir_buff);
}

char	*init_cwd(t_data *d)
{
	char	*pwd_export;

	pwd_export = get_env_value(d, d->env_list, "PWD");
	if (!pwd_export)
		pwd_export = custom_get_cwd(d);
	set_key_value(d, d->env_list, "PWD", pwd_export);
	return (pwd_export);
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
	set_key_value(data, data->env_list, "PWD", working_dir_buff);
	data->cwd = working_dir_buff;
	return (1);
}

static int	init_data_directories(t_data *d, char *path)
{
	char	*truncated_path;

	d->start_wd = init_cwd(d);
	truncated_path = get_env_value(d, d->env_list, "MSH");
	if (truncated_path)
		d->msh_wd = ms_strdup(d, truncated_path);
	else
	{
		truncated_path = truncate_at_end(path + 1, '/');
		d->msh_wd = ms_strjoin(d, d->start_wd, truncated_path);
	}
	safe_free(truncated_path);
	d->man_wd = ms_strjoin(d, d->msh_wd, "/doc/");
	d->heredoc_wd = ms_strjoin(d, d->msh_wd, "/ressources/.heredoc.txt");
	d->history_wd = ms_strjoin(d, d->msh_wd, "/ressources/.history.txt");
	read_history(d->history_wd);
	return (1);
}

void	init_base_stds(t_data *data)
{
	data->saved_stdin = -1;
	data->saved_stdout = -1;
	data->heredocfd = -1;
	data->base_stdin = dup(STDIN_FILENO);
	data->base_stdout = dup(STDOUT_FILENO);
	if (data->base_stdin == -1 || data->base_stdout == -1)
		custom_exit(data, "failed to save stds", NULL, EXIT_FAILURE);
}

void	init_data(t_data *data, char *path, char **env)
{
	init_base_stds(data);
	data->cwd = NULL;
	data->prev_cwd = NULL;
	data->home_wd = NULL;
	data->logname = NULL;
	data->man_wd = NULL;
	data->msh_wd = NULL;
	data->start_wd = NULL;
	data->environ = NULL;
	data->env_list = NULL;
	data->tmp_list = NULL;
	data->var_list = NULL;
	data->prv_input = NULL;
	data->brackets = 0;
	data->fork_child = 0;
	data->last_exit = 0;
	g_quit_in_heredoc = 0;
	init_env_list(data, env);
	data->environ = dblst_to_arr(data->env_list);
	update_env_variables(data);
	init_data_directories(data, path);
	update_cwd(data);
	init_builtins_data(data);
	export_usefull_var(data);
}
