/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bltn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:47:21 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/31 18:12:05 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static void	init_builtins_pointers(t_data *data)
{
	data->blt_fct[e_cd] = cd;
	data->blt_fct[e_clear] = clear;
	data->blt_fct[e_echo] = echo;
	data->blt_fct[e_env] = env;
	data->blt_fct[e_exec] = exec;
	data->blt_fct[e_exit] = custom_exit;
	data->blt_fct[e_export] = export;
	data->blt_fct[e_ls] = ls;
	data->blt_fct[e_man] = man;
	data->blt_fct[e_pwd] = pwd;
	data->blt_fct[e_unset] = unset;
}

static void	init_builtins_names(t_data *data)
{
	data->bltin_names = malloc(12 * sizeof(char *));
	if (!data->bltin_names)
		custom_exit(data, "Bltin_names alloc failed", NULL, EXIT_FAILURE);
	data->bltin_names[e_cd] = ms_strdup(data, "cd");
	data->bltin_names[e_clear] = ms_strdup(data, "clear");
	data->bltin_names[e_echo] = ms_strdup(data, "echo");
	data->bltin_names[e_env] = ms_strdup(data, "env");
	data->bltin_names[e_exec] = ms_strdup(data, "exec");
	data->bltin_names[e_exit] = ms_strdup(data, "exit");
	data->bltin_names[e_export] = ms_strdup(data, "export");
	data->bltin_names[e_ls] = ms_strdup(data, "ls");
	data->bltin_names[e_man] = ms_strdup(data, "man");
	data->bltin_names[e_pwd] = ms_strdup(data, "pwd");
	data->bltin_names[e_unset] = ms_strdup(data, "unset");
	data->bltin_names[11] = NULL;
}

void	init_builtins_data(t_data *d)
{
	init_builtins_names(d);
	init_builtins_pointers(d);
}
