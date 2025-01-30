/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bltn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:47:21 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/30 11:01:03 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	init_builtins_pointers(t_data *data)
{
	data->builtin_funcs[e_cd] = cd;
	data->builtin_funcs[e_clear] = clear;
	data->builtin_funcs[e_echo] = echo;
	data->builtin_funcs[e_env] = env;
	data->builtin_funcs[e_exec] = exec;
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

	data->bltin_names = malloc(12 * sizeof(char *));
	if (!data->bltin_names)
		custom_exit(data, "Bltin_names alloc failed", NULL, EXIT_FAILURE);
	data->bltin_names[e_cd] = ft_strdup("cd");
	data->bltin_names[e_clear] = ft_strdup("clear");
	data->bltin_names[e_echo] = ft_strdup("echo");
	data->bltin_names[e_env] = ft_strdup("env");
	data->bltin_names[e_exec] = ft_strdup("exec");
	data->bltin_names[e_exit] = ft_strdup("exit");
	data->bltin_names[e_export] = ft_strdup("export");
	data->bltin_names[e_ls] = ft_strdup("ls");
	data->bltin_names[e_man] = ft_strdup("man");
	!data->bltin_names[e_man] && (custom_exit(data, NULL, NULL, EXIT_FAILURE));
	data->bltin_names[e_pwd] = ft_strdup("pwd");
	data->bltin_names[e_unset] = ft_strdup("unset");
	data->bltin_names[11] = NULL;
	i = -1;
	while (data->bltin_names[++i])
		continue ;
	if (i != 11)
		custom_exit(data, "Bltin_names alloc failed", NULL, EXIT_FAILURE);
}

void	init_builtins_data(t_data *d)
{
	init_builtins_names(d);
	init_builtins_pointers(d);
}
