/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:41:32 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/28 15:52:12 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	*get_dir_in_path(t_data *d, char *cmd_name)
{
	char	*path_env;
	char	**splitted_path;
	char	*cmd_path;
	int		i;

	path_env = get_env_value(d, d->env_list, "PATH");
	if (!path_env)
		custom_exit(d, "PATH not found in environment", NULL, EXIT_FAILURE);
	splitted_path = ft_split(path_env, ':');
	free(path_env);
	if (!splitted_path)
		custom_exit(d, "Failed to split PATH", NULL, EXIT_FAILURE);
	cmd_path = NULL;
	i = -1;
	while (splitted_path[++i])
	{
		cmd_path = ft_str_mega_join(splitted_path[i], "/", cmd_name, NULL);
		if (access(cmd_path, X_OK) == 0)
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	free_void_array((void ***)&splitted_path);
	return (cmd_path);
}

int	search_true_cmd(t_data *d, char *cmd_name, char *arg, char **flags)
{
	char	*path_cmd;

	path_cmd = get_dir_in_path(d, cmd_name);
	if (path_cmd)
	{
		printf("____________True shell cmd outpout________\n");
		handle_direct_exec(d, path_cmd, arg, flags);
		printf("____________minishell command__________\n");
		return (1);
	}
	return (0);
}
