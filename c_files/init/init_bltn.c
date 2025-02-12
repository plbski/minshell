/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bltn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:47:21 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/12 14:43:24 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static void	init_types_names(t_data *d)
{
	d->types_names = malloc(sizeof(char *) * 15);
	if (!d->types_names)
		custom_exit(d, "alloc in types names", NULL, EXIT_FAILURE);
	d->types_names[0] = ms_strdup(d, "command");
	d->types_names[1] = ms_strdup(d, "argument");
	d->types_names[2] = ms_strdup(d, "expanded argument");
	d->types_names[3] = ms_strdup(d, "redir in");
	d->types_names[4] = ms_strdup(d, "redir out");
	d->types_names[5] = ms_strdup(d, "append");
	d->types_names[6] = ms_strdup(d, "heredoc");
	d->types_names[7] = ms_strdup(d, "pipe");
	d->types_names[8] = ms_strdup(d, "logical");
	d->types_names[9] = ms_strdup(d, "quote");
	d->types_names[10] = ms_strdup(d, "dbquote");
	d->types_names[11] = ms_strdup(d, "wildcard");
	d->types_names[12] = ms_strdup(d, "flag");
	d->types_names[13] = ms_strdup(d, "exec");
	d->types_names[14] = NULL;
}

static void	init_builtins_pointers(t_data *data)
{
	data->blt_fct[e_cd] = cd;
	data->blt_fct[e_echo] = echo;
	data->blt_fct[e_env] = env;
	data->blt_fct[e_exec] = exec;
	data->blt_fct[e_exit] = custom_exit;
	data->blt_fct[e_export] = export;
	data->blt_fct[e_doc] = doc;
	data->blt_fct[e_pwd] = pwd;
	data->blt_fct[e_unset] = unset;
}

static void	init_builtins_names(t_data *data)
{
	data->bltin_names = malloc(10 * sizeof(char *));
	if (!data->bltin_names)
		custom_exit(data, "Bltin_names alloc failed", NULL, EXIT_FAILURE);
	data->bltin_names[e_cd] = ms_strdup(data, "cd");
	data->bltin_names[e_echo] = ms_strdup(data, "echo");
	data->bltin_names[e_env] = ms_strdup(data, "env");
	data->bltin_names[e_exec] = ms_strdup(data, "exec");
	data->bltin_names[e_exit] = ms_strdup(data, "exit");
	data->bltin_names[e_export] = ms_strdup(data, "export");
	data->bltin_names[e_doc] = ms_strdup(data, "doc");
	data->bltin_names[e_pwd] = ms_strdup(data, "pwd");
	data->bltin_names[e_unset] = ms_strdup(data, "unset");
	data->bltin_names[9] = NULL;
}

void	export_usefull_var(t_data *d)
{
	if (d->debug_mode)
		dblst_add_back(&d->var_list, dblst_new(ms_strdup(d, "deb=1")));
	else
		dblst_add_back(&d->var_list, dblst_new(ms_strdup(d, "deb=0")));
	if (!get_dblst_at_key(d->env_list, "SHLVL"))
		export(d, ms_strdup(d, "SHLVL=1"), NULL, 0);
}

void	init_builtins_data(t_data *d)
{
	init_builtins_names(d);
	init_builtins_pointers(d);
	init_types_names(d);
}
