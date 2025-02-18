/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:30:44 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/17 23:20:31 by giuliovalen      ###   ########.fr       */
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
		cmd_path = ft_megajoin(splitted_path[i], "/", cmd_name, NULL);
		if (access(cmd_path, X_OK) == 0)
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	free_void_array((void ***)&splitted_path);
	return (cmd_path);
}

char	*handle_path_in_dir(t_data *d, char *prg, int is_indirect)
{
	char		*path_dir;

	path_dir = get_dir_in_path(d, prg);
	if (path_dir && is_valid_exec_file(path_dir, &is_indirect, is_indirect))
		return (path_dir);
	safe_free(path_dir);
	if (is_directory(prg))
	{
		if (!is_indirect)
			ft_dprintf(2, "msh: exec: %s: \
cannot execute: Is a directory\n", prg);
		else
			ft_dprintf(2, "msh: %s: command not found\n", prg);
	}
	else if (access(prg, X_OK) == -1 && prg[0] == '.' && prg[1] == '/')
		ft_dprintf(2, "msh: %s: Permission denied\n", prg);
	else if (access(prg, F_OK) == -1)
	{
		if (!is_indirect)
			ft_dprintf(2, "msh: exec: %s: not found\n", prg);
		else
			ft_dprintf(2, "msh: %s: command not found\n", prg);
	}
	return (NULL);
}

int	is_valid_exec_file(const char *file, int *fct_ret, int is_direct)
{
	struct stat	st;
	int			fd;
	char		buf[4];

	(void)is_direct;
	if (is_directory(file))
		return (*fct_ret = 126, 0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (*fct_ret = 127, 0);
	if (fstat(fd, &st) == -1 || !S_ISREG(st.st_mode) || !(st.st_mode & S_IXUSR))
		return (*fct_ret = 126, close(fd), 0);
	if (read(fd, buf, 4) != 4)
		return (*fct_ret = 127, close(fd), 0);
	close(fd);
	return (1);
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
