/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:54:32 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/15 00:13:28 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	update_cwd(t_data *data)
{
	char	*working_dir_buff;

	working_dir_buff = malloc(MAX_DIR_LEN);
	if (!working_dir_buff)
		return (data->status = closing, 0);
	if (!getcwd(working_dir_buff, MAX_DIR_LEN))
		return (free(working_dir_buff), data->status = closing, 0);
	return (data->cwd = working_dir_buff, 1);
}

int	init_data_directories(t_data *data)
{
	char	*working_dir_buff;

	working_dir_buff = malloc(MAX_DIR_LEN);
	if (!working_dir_buff)
		return (data->status = closing, 0);
	if (!getcwd(working_dir_buff, MAX_DIR_LEN))
		return (free(working_dir_buff), data->status = closing, 0);
	data->start_wd = working_dir_buff;
	data->doc_wd = ft_strjoin(working_dir_buff, "/DOC/");
	return (1);
}

int	init_cwd(t_data *data)
{
	init_data_directories(data);
	if (chdir("/home/") == -1)
		return (printf("ERROR\n"), 0);
	update_cwd(data);
	return (1);
}

void	init_data(t_data *data)
{
	data->status = running;
	init_cwd(data);
	init_env(data);
}

int	init_env(t_data *data)
{
	char	*env;

	env = getenv("PATH");
	if (!env)
		return (data->status = closing, 0);
	printf("Env received:\n\"%s\"\n\n", env);
	return (1);
}
