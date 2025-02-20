/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:30:44 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/20 22:46:19 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

void	print_exec_error_2(const char *arg, int st, int loca)
{
	const char	*exc_lc[3] = {"is a directory", "Permission denied", \
		"No such file or directory"};
	const char	*exc_lc2[3] = {"cannot execute: Undefined error: 0", \
		"cannot execute", exc_lc2[0]};
	const char	*exc_call[3] = {"not found", "Permission denied", "not found"};
	const char	*exc_cl2[3] = {NULL, exc_lc2[1], NULL};

	ft_dprintf(2, "msh: exec: %s: ", arg);
	if (loca)
	{
		ft_dprintf(2, "%s\n", exc_lc[st]);
		ft_dprintf(2, "msh: exec: %s :", arg);
		ft_dprintf(2, "%s\n", exc_lc2[st]);
	}
	else
	{
		ft_dprintf(2, "%s\n", exc_call[st]);
		if (exc_cl2[st])
		{
			ft_dprintf(2, "msh: exec: %s :", arg);
			ft_dprintf(2, "%s\n", exc_cl2[st]);
		}
	}
}

void	print_exec_error(const char *arg, int status, int is_exec)
{
	const char	*no_exc_lc[3] = {"is a directory", "Permission denied", \
		"No such file or directory"};
	const char	*no_exc[3] = {"command not found", no_exc_lc[1], no_exc[0]};
	int			is_local;

	is_local = (arg[0] == '/' || !ft_strncmp(arg, "./", 2));
	if (status > 2)
		status -= 125;
	if (!is_exec)
	{
		ft_dprintf(2, "msh: %s ", arg);
		if (is_local)
			ft_dprintf(2, "%s\n", no_exc_lc[status]);
		else
			ft_dprintf(2, "%s\n", no_exc[status]);
	}
	else
		print_exec_error_2(arg, status, is_local);
}

char	**set_argv(t_data *d, char *prog_name, char **args, int args_len)
{
	char	**new_argv;
	int		i;

	new_argv = ms_malloc(d, sizeof(char *) * (2 + args_len));
	new_argv[0] = ms_strdup(d, prog_name);
	i = -1;
	while (++i < args_len && args && args[i])
		new_argv[i + 1] = ms_strdup(d, args[i]);
	new_argv[i + 1] = NULL;
	return (new_argv);
}

char	*fetch_path(t_data *d, char *cmd_name)
{
	char	*path_env;
	char	**splitted_path;
	char	*cmd_path;
	int		i;

	path_env = get_env_value(d, d->env_list, "PATH");
	if (!path_env)
		return (ft_megajoin(d->cwd, "/", cmd_name, NULL));
	splitted_path = ft_split(path_env, ':');
	free(path_env);
	if (!splitted_path)
		custom_exit(d, "Failed to split PATH", NULL, EXIT_FAILURE);
	cmd_path = NULL;
	i = -1;
	while (splitted_path[++i])
	{
		cmd_path = ft_megajoin(splitted_path[i], "/", cmd_name, NULL);
		if (access(cmd_path, F_OK) == 0 && !is_directory(cmd_path))
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	free_void_array((void ***)&splitted_path);
	return (cmd_path);
}

char	*get_path_in_env(t_data *d, char *prg, int is_exec, int *fct_ret)
{
	char		*path_dir;

	path_dir = fetch_path(d, prg);
	if (!path_dir)
	{
		print_exec_error(prg, CMD_NOT_FOUND, is_exec);
		return (NULL);
	}
	if (valid_exec(path_dir, fct_ret, is_exec, 0))
		return (path_dir);
	valid_exec(prg, fct_ret, is_exec, 0);
	print_exec_error(prg, *fct_ret, is_exec);
	return (NULL);
}
