/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:23:52 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/13 15:41:07 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	handle_child_process(t_data *d, char *program, char **argv)
{
	char	**new_args;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	increment_shlvl(d);
	update_environ(d);
	execve(program, argv, d->environ);
	new_args = malloc(sizeof(char *) * 2);
	new_args[0] = ms_strdup(d, "/bin/sh");
	new_args[1] = ms_strdup(d, program);
	new_args[2] = NULL;
	execve("/bin/sh", new_args, d->environ);
	custom_exit(d, NULL, NULL, EXIT_FAILURE);
	return (FCT_FAIL);
}

int	handle_parent_process(pid_t child_pid)
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

static char	*validate_exec(t_data *d, char *prg, int is_indirect)
{
	if (prg[0] == '.' && !prg[1])
	{
		ft_dprintf(2, ".: usage: . filename [arguments]\n");
		return (NULL);
	}
	if (prg[0] == '.' && prg[1] == '/')
	{
		if (is_directory(prg))
			ft_dprintf(2, "msh: %s: Is a directory\n", prg);
		else if (access(prg, F_OK) == -1)
			ft_dprintf(2, "msh: %s: no such file or directory\n", prg);
		else
			ft_dprintf(2, "msh: %s: Permission denied\n", prg);
		return (NULL);
	}
	return (handle_path_in_dir(d, prg, is_indirect));
}

int	exec(t_data *d, char *prg, char **argv, int is_indirect)
{
	pid_t		child_pid;
	char		*new_prg;

	if (cmp_str(prg, "exec") || !prg)
		return (FCT_SUCCESS);
	if (!argv || !argv[0])
	{
		free_void_array((void ***)&argv);
		argv = set_argv(d, prg);
	}
	if (!is_valid_exec_file(prg))
		new_prg = validate_exec(d, prg, is_indirect);
	else
		new_prg = ms_strdup(d, prg);
	if (!new_prg)
		return (CMD_NOT_FOUND);
	child_pid = fork();
	if (child_pid == 0)
		return (handle_child_process(d, new_prg, argv));
	d->last_exit_st = handle_parent_process(child_pid);
	return (free(new_prg), FCT_SUCCESS);
}
