/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:54:32 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/24 14:06:06 by giuliovalen      ###   ########.fr       */
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

void	init_builtins_pointers(t_data *data)
{
	data->builtin_funcs[e_cd] = cd;
	data->builtin_funcs[e_clear] = clear;
	data->builtin_funcs[e_echo] = echo;
	data->builtin_funcs[e_env] = env;
	data->builtin_funcs[e_exit] = custom_exit;
	data->builtin_funcs[e_export] = export;
	data->builtin_funcs[e_ls] = ls;
	data->builtin_funcs[e_man] = man;
	data->builtin_funcs[e_pwd] = pwd;
	data->builtin_funcs[e_unset] = unset;
}

void	init_builtins_names(t_data *data)
{
	int	i;

	data->bltin_names = malloc(11 * sizeof(char *));
	if (!data->bltin_names)
		custom_exit(data, NULL, NULL, 0);
	data->bltin_names[e_cd] = ft_strdup("cd");
	data->bltin_names[e_clear] = ft_strdup("clear");
	data->bltin_names[e_echo] = ft_strdup("echo");
	data->bltin_names[e_env] = ft_strdup("env");
	data->bltin_names[e_exit] = ft_strdup("exit");
	data->bltin_names[e_export] = ft_strdup("export");
	data->bltin_names[e_ls] = ft_strdup("ls");
	data->bltin_names[e_man] = ft_strdup("man");
	data->bltin_names[e_pwd] = ft_strdup("pwd");
	data->bltin_names[e_unset] = ft_strdup("unset");
	data->bltin_names[10] = NULL;
	i = -1;
	while (data->bltin_names[++i])
		continue ;
	if (i != 10)
		custom_exit(data, NULL, NULL, 0);
	init_builtins_pointers(data);
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

void	init_data(t_data *data, char **env)
{
	g_sa_quit = 0;
	data->status = running;
	data->cwd = NULL;
	data->prev_cwd = NULL;
	data->start_wd = NULL;
	data->home_wd = NULL;
	data->logname = NULL;
	data->doc_wd = NULL;
	data->environ = NULL;
	data->env_list = NULL;
	update_env_list(data, env);
	data->environ = list_to_arr(data->env_list);
	update_env_variables(data);
	init_cwd(data);
	init_builtins_names(data);
}
