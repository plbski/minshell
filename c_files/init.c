/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:54:32 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/15 18:07:04 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*get_home(char *working_dir_buff)
{
	int	i;
	int	j; 
	
	i = 0;
	j = 0;
	while (working_dir_buff[j])
	{
		if (working_dir_buff[j] == '/')
			i ++;
		if (i > 2)
		{
			working_dir_buff[j] = '\0';
			break;
		}
		j ++;
	}
	return (working_dir_buff);
}

char	*init_cwd(t_data *data)
{
	char	*working_dir_buff;

	data->status = running;
	working_dir_buff = malloc(MAX_DIR_LEN);
	if (!working_dir_buff)
		return (data->status = closing, NULL);
	if (!getcwd(working_dir_buff, MAX_DIR_LEN))
	{
		free(working_dir_buff);
		return (data->status = closing, NULL);
	}
	working_dir_buff = get_home(working_dir_buff);
	data->home = ft_strdup(working_dir_buff);
	data->cwd =working_dir_buff;
	return (data->cwd);
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
