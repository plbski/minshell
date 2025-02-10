/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:23:52 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/10 12:31:43 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	increment_shlvl(t_data *d)
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

static int	handle_child_process(t_data *d, char *program, char **argv)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	increment_shlvl(d);
	update_environ(d);
	execve(program, argv, d->environ);
	printf("\"%s\" exec failed\n", program);
	custom_exit(d, NULL, NULL, EXIT_FAILURE);
	return (FCT_FAIL);
}

static int	handle_parent_process(pid_t child_pid)
{
	int	wait_status;

	setup_signal(1, 0);
	if (waitpid(child_pid, &wait_status, 0) == -1)
	{
		perror("waitpid");
		return (FCT_FAIL);
	}
	setup_signal(0, 0);
	if (WIFEXITED(wait_status))
		return (WEXITSTATUS(wait_status));
	else if (WIFSIGNALED(wait_status))
		return (128 + WTERMSIG(wait_status));
	return (-1);
}

static int	validate_exec(const char *file)
{
	struct stat	st;
	int			fd;
	char		buf[4];

	if (is_directory(file))
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	if (fstat(fd, &st) == -1 || !S_ISREG(st.st_mode))
		return (0);
	if (read(fd, buf, 4) != 4)
		return (0);
	close(fd);
	return (1);
}

int	exec(t_data *d, char *prg, char **argv, int u __attribute__((unused)))
{
	pid_t		child_pid;
	char		*path_cmd;

	if (!argv || !argv[0])
	{
		free_void_array((void ***)&argv);
		argv = set_argv(d, prg);
	}
	if (!validate_exec(prg))
	{
		path_cmd = get_dir_in_path(d, prg);
		if (!path_cmd || !validate_exec(path_cmd))
		{
			if (path_cmd)
				free(path_cmd);
			if (access(prg, X_OK) == -1)
				ft_dprintf(2, "msh: %s: Permission denied\n", prg);
			else
				ft_dprintf(2, "msh: exec: %s: not found\n", prg);
			return (CMD_NOT_FOUND);
		}
		free(prg);
		prg = path_cmd;
	}
	child_pid = fork();
	if (child_pid == 0)
		return (handle_child_process(d, prg, argv));
	else
	{
		d->last_exit_status = handle_parent_process(child_pid);
		return (printf("\n"), FCT_SUCCESS);
	}
}
