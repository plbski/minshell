/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:58:30 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/21 00:10:24 by giuliovalen      ###   ########.fr       */
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
