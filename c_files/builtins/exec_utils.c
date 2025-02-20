/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:30:44 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/20 01:37:08 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

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
		print_exec_error(prg, CMD_NOT_FOUND, is_exec, 0);
		return (NULL);
	}
	if (valid_exec(path_dir, fct_ret, is_exec, 0, 0))
		return (path_dir);
	valid_exec(prg, fct_ret, is_exec, 0, 0);
	printf("FCT RET %d %s\n", *fct_ret, prg);
	if (!ft_strncmp(prg, "./", 2) || prg[0] == '/')
		print_exec_error(prg, *fct_ret, is_exec, 1);
	else
		print_exec_error(prg, *fct_ret, is_exec, 0);
	return (NULL);
}

int	increment_shlvl(t_data *d)
{
	t_dblist	*element;
	char		*new_lvl;
	char		*new_content;

	element = get_dblst_at_key(d->env_list, "SHLVL");
	if (!element)
		return (0);
	new_lvl = ft_itoa(d->shlvl);
	if (!new_lvl)
		return (custom_exit(d, "SHLVL alloc failed", NULL, EXIT_FAILURE));
	new_content = ft_megajoin("SHLVL", "=", new_lvl, NULL);
	free(new_lvl);
	setstr(d, (char **)&element->content, new_content);
	return (1);
}

void	print_exec_error(const char *arg, int status, int is_exec, int is_local)
{
	printf("[error called: %s %d %d %d]\n\n", arg, status, is_exec, is_local);
	if (status == CMD_NOT_EXEC)
	{
		ft_dprintf(2, "msh: %s: Permission denied\n", arg);
		if (is_exec)
			ft_dprintf(2, "msh: exec: %s: cannot execute: \
Undefined error: 0\n", arg);
		return ;
	}
	if (status == CMD_NOT_FOUND && is_local)
		ft_dprintf(2, "msh: %s: No such file or directory\n", arg);
	if (status == CMD_NOT_FOUND && is_exec && is_local)
		ft_dprintf(2, "msh: exec: %s: cannot execute: \
No such file or directory\n", arg);
	if (status == ERR_IS_DIR)
	{
		if (is_exec && !is_local)
			ft_dprintf(2, "msh: exec: command not found\n");
		if (!is_exec)
			ft_dprintf(2, "msh: %s: is a directory\n", arg);
		if (is_exec && is_local)
			ft_dprintf(2, "msh: exec: %s: \
cannot execute: Undefined error: 0\n", arg);
	}
	if (!is_local && is_exec)
		ft_dprintf(2, "msh: exec %s: command not found\n", arg);
	else if (!is_local)
		ft_dprintf(2, "msh: %s: command not found\n", arg);
}
