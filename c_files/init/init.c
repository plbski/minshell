/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:54:32 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/20 23:25:07 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

void	init_cwd(t_data *d)
{
	char	*pwd_export;

	pwd_export = get_env_value(d, d->env_list, "PWD");
	if (!pwd_export)
		pwd_export = custom_get_cwd(d);
	set_key_value(d, d->env_list, "PWD", pwd_export);
	d->start_wd = pwd_export;
}

static int	init_msh_directories(t_data *d, char *path)
{
	char	*truncated_path;

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

void	init_data_var(t_data *d)
{
	d->cwd = NULL;
	d->prev_cwd = NULL;
	d->home_wd = NULL;
	d->logname = NULL;
	d->man_wd = NULL;
	d->msh_wd = NULL;
	d->start_wd = NULL;
	d->environ = NULL;
	d->env_list = NULL;
	d->tmp_list = NULL;
	d->var_list = NULL;
	d->prv_input = NULL;
	d->brackets = 0;
	d->fork_child = 0;
	d->last_exit = 0;
}

void	init_msh_data(t_data *data, char *path, char **env)
{
	g_quit_in_heredoc = 0;
	init_data_var(data);
	init_base_stds(data);
	init_env_list(data, env);
	data->environ = dblst_to_arr(data->env_list);
	update_env_variables(data);
	init_cwd(data);
	init_msh_directories(data, path);
	update_cwd(data);
	init_builtins_data(data);
	export_usefull_var(data);
}
