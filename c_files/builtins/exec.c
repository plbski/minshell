/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:23:52 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/21 19:10:19 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static int	handle_child(t_data *d, char *prg, char **argv)
{
	char	**new_args;

	d->fork_child++;
	if (ft_strstr(prg, ".sh") && argv[0] && !same_str(argv[0], prg))
	{
		new_args = set_argv(d, prg, argv, get_arr_len((void **)argv));
		free_void_array((void ***)&argv);
		argv = new_args;
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	update_environ(d);
	execve(prg, argv, d->environ);
	setstr(d, &argv[0], ms_strdup(d, "/bin/sh"));
	execve("/bin/sh", argv, d->environ);
	free_void_array((void ***)&new_args);
	return (FCT_FAIL);
}

static int	handle_parent(pid_t child_pid)
{
	int		wait_status;

	setup_signal(1, 0);
	if (waitpid(child_pid, &wait_status, 0) == -1)
		return (perror("waitpid"), -1);
	setup_signal(0, 0);
	if (WIFEXITED(wait_status))
		return (WEXITSTATUS(wait_status));
	else if (WIFSIGNALED(wait_status))
	{
		printf("\n");
		return (128 + WTERMSIG(wait_status));
	}
	return (-1);
}

static char	*validate_exec(t_data *d, char *prg, int is_direct, int *ret_val)
{
	char	*new_path;

	if (same_str(prg, "."))
		return (ft_dprintf(2, ".: usage: . filename [arguments]\n"), NULL);
	new_path = get_path_in_env(d, prg, !is_direct, ret_val);
	if (!new_path && is_direct)
		*ret_val = CMD_NOT_FOUND;
	else if (!new_path)
		*ret_val = CMD_NOT_EXEC;
	return (new_path);
}

int	valid_exec(const char *file, int *fct_ret, int exec, int prnt)
{
	struct stat	st;
	int			fd;
	char		buff[4];

	*fct_ret = FCT_OK;
	if (is_directory(file))
	{
		if (prnt)
			print_exec_error(file, ERR_IS_DIR, exec);
		return (*fct_ret = CMD_IS_DIR, 0);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1 || access(file, F_OK) == -1)
		*fct_ret = CMD_NOT_FOUND;
	else if (fstat(fd, &st) == -1 || \
		!S_ISREG(st.st_mode) || !(st.st_mode & S_IXUSR))
		*fct_ret = CMD_NOT_EXEC;
	if (*fct_ret == FCT_OK && read(fd, buff, 4) < 4)
		return (close(fd), 0);
	close(fd);
	if (*fct_ret == FCT_OK)
		return (1);
	if (prnt)
		print_exec_error(file, *fct_ret, exec);
	return (0);
}

int	exec(t_data *d, char *prg, char **argv, int is_direct)
{
	pid_t		child_pid;
	char		*prg_path;
	int			st;

	if (!prg || same_str(prg, "exec"))
		return (FCT_OK);
	prg_path = NULL;
	if ((*prg == '/' || !ft_strncmp(prg, "./", 2)) && \
		valid_exec(prg, &st, !is_direct, 1))
		prg_path = ms_strdup(d, prg);
	else if (prg[0] != '/' && ft_strncmp(prg, "./", 2))
		prg_path = validate_exec(d, prg, is_direct, &st);
	if (!prg_path)
		return (st);
	if (!argv || !argv[0])
		set_strarr(&argv, set_argv(d, prg_path, NULL, 0));
	else if (!is_direct)
		argv = set_argv(d, prg_path, argv, get_arr_len((void **)argv));
	child_pid = fork();
	if (child_pid == -1)
		return (perror("fork"), -1);
	if (child_pid == 0)
		return (handle_child(d, prg_path, argv));
	return (free(prg_path), handle_parent(child_pid));
}
