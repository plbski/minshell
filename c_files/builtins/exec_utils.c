/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:30:44 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/12 12:18:41 by giuliovalen      ###   ########.fr       */
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
	if (!path_dir || !is_valid_exec_file(path_dir))
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

int	is_valid_exec_file(const char *file)
{
	struct stat	st;
	int			fd;
	char		buf[4];

	if (is_directory(file))
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	if (fstat(fd, &st) == -1 || !S_ISREG(st.st_mode) || !(st.st_mode & S_IXUSR))
		return (0);
	if (read(fd, buf, 4) != 4)
		return (0);
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
	new_content = ft_str_mega_join("SHLVL", "=", new_lvl, NULL);
	free(new_lvl);
	if (!new_content)
		return (custom_exit(d, "SHLVL alloc failed", NULL, EXIT_FAILURE));
	free(element->content);
	element->content = new_content;
	return (1);
}
