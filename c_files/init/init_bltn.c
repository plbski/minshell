/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bltn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:47:21 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/21 11:23:24 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static void	init_types_names(t_data *d)
{
	d->types_names = ms_malloc(d, sizeof(char *) * 10);
	d->types_names[tk_cmd] = ms_strdup(d, "cmd");
	d->types_names[tk_arg] = ms_strdup(d, "arg");
	d->types_names[tk_red_in] = ms_strdup(d, "red_in");
	d->types_names[tk_red_out] = ms_strdup(d, "red_out");
	d->types_names[tk_red_app] = ms_strdup(d, "red_app");
	d->types_names[tk_hered] = ms_strdup(d, "hered");
	d->types_names[tk_pipe] = ms_strdup(d, "pipe");
	d->types_names[tk_logical] = ms_strdup(d, "logic");
	d->types_names[tk_wildcard] = ms_strdup(d, "wildc");
	d->types_names[9] = NULL;
}

static void	init_builtins_pointers(t_data *data)
{
	data->blt_fct[e_cd] = cd;
	data->blt_fct[e_echo] = echo;
	data->blt_fct[e_ls] = ls;
	data->blt_fct[e_env] = env;
	data->blt_fct[e_exec] = exec;
	data->blt_fct[e_exit] = custom_exit;
	data->blt_fct[e_export] = export;
	data->blt_fct[e_doc] = doc;
	data->blt_fct[e_pwd] = pwd;
	data->blt_fct[e_unset] = unset;
	data->blt_fct[e_source] = source;
}

static void	init_builtins_names(t_data *data)
{
	data->bltin_names = ms_malloc(data, 12 * sizeof(char *));
	data->bltin_names[e_cd] = ms_strdup(data, "cd");
	data->bltin_names[e_echo] = ms_strdup(data, "echo");
	data->bltin_names[e_ls] = ms_strdup(data, "mls");
	data->bltin_names[e_env] = ms_strdup(data, "env");
	data->bltin_names[e_exec] = ms_strdup(data, "exec");
	data->bltin_names[e_exit] = ms_strdup(data, "exit");
	data->bltin_names[e_export] = ms_strdup(data, "export");
	data->bltin_names[e_doc] = ms_strdup(data, "doc");
	data->bltin_names[e_pwd] = ms_strdup(data, "pwd");
	data->bltin_names[e_unset] = ms_strdup(data, "unset");
	data->bltin_names[e_source] = ms_strdup(data, "source");
	data->bltin_names[11] = NULL;
}

void	export_usefull_var(t_data *d)
{
	char	*shlvl;

	if (!get_dblst_at_key(d->env_list, "MSH"))
		dblst_add_back(&d->env_list, \
dblst_new(ms_strjoin(d, "MSH=", d->msh_wd)));
	if (!get_dblst_at_key(d->env_list, "SHLVL"))
		export(d, ms_strdup(d, "SHLVL=1"), NULL, 0);
	shlvl = get_env_value(d, d->env_list, "SHLVL");
	if (!shlvl)
		custom_exit(d, "alloc shlvl failed", NULL, EXIT_FAILURE);
	d->shlvl = ft_atoi(shlvl) + 1;
	setstr(d, &shlvl, ft_itoa(d->shlvl));
	set_key_value(d, d->env_list, "SHLVL", shlvl);
	free(shlvl);
}

void	init_builtins_data(t_data *d)
{
	init_builtins_names(d);
	init_builtins_pointers(d);
	init_types_names(d);
	source(d, NULL, NULL, 0);
}
