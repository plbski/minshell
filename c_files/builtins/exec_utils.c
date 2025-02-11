/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:30:44 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/11 13:04:20 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	**set_argv(t_data *d, char *prog_name)
{
	char	**new_argv;

	new_argv = malloc(sizeof(char *) * 2);
	if (!new_argv)
		custom_exit(d, "Exec argv error", NULL, EXIT_FAILURE);
	new_argv[0] = ms_strdup(d, prog_name);
	new_argv[1] = NULL;
	return (new_argv);
}

char	*get_dir_in_path(t_data *d, char *cmd_name)
{
	char	*path_env;
	char	**splitted_path;
	char	*cmd_path;
	int		i;

	path_env = get_env_value(d, d->env_list, "PATH");
	if (!path_env)
		return (NULL);
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

char	*handle_path_in_dir(t_data *d, char *prg)
{
	char		*path_dir;

	path_dir = get_dir_in_path(d, prg);
	if (!path_dir || !validate_exec(path_dir))
	{
		if (path_dir)
			free(path_dir);
		if (access(prg, F_OK) == -1 || is_directory(prg))
			ft_dprintf(2, "msh: exec: %s: not found\n", prg);
		else
			ft_dprintf(2, "msh: %s: Permission denied\n", prg);
		return (NULL);
	}
	return (path_dir);
}
