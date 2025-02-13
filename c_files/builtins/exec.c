/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:23:52 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/13 21:58:38 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	handle_child(t_data *d, char *prg, char **argv)
{
	char	**new_args;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	increment_shlvl(d);
	update_environ(d);
	execve(prg, argv, d->environ);
	new_args = ms_malloc(d, sizeof(char *) * 3);
	new_args[0] = ms_strdup(d, "/bin/sh");
	new_args[1] = ms_strdup(d, prg);
	new_args[2] = NULL;
	execve("/bin/sh", new_args, d->environ);
	free_void_array((void ***)&new_args);
	custom_exit(d, NULL, NULL, EXIT_FAILURE);
	return (FCT_FAIL);
}

static int	handle_parent(t_data *d, pid_t child_pid)
{
	int		wait_status;

	(void)d;
	setup_signal(1, 0);
	if (waitpid(child_pid, &wait_status, 0) == -1)
		return (perror("waitpid"), -1);
	setup_signal(0, 0);
	if (WIFEXITED(wait_status))
		return (WEXITSTATUS(wait_status));
	else if (WIFSIGNALED(wait_status))
		return (128 + WTERMSIG(wait_status));
	return (-1);
}

static char	*validate_exec(t_data *d, char *prg, int is_indirect, int *ret_val)
{
	char	*new_path;

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
	new_path = handle_path_in_dir(d, prg, is_indirect);
	if (!new_path && is_indirect)
		*ret_val = 127;
	else if (!new_path)
		*ret_val = 126;
	return (new_path);
}

int	exec(t_data *d, char *prg, char **argv, int is_indirect)
{
	pid_t		child_pid;
	char		*new_prg;
	int			ret_val;

	if (cmp_str(prg, "exec") || !prg)
		return (FCT_SUCCESS);
	if (!is_valid_exec_file(prg, &ret_val, is_indirect))
		new_prg = validate_exec(d, prg, is_indirect, &ret_val);
	else
		new_prg = ms_strdup(d, prg);
	if (!new_prg)
		return (ret_val);
	if (!argv || !argv[0])
	{
		free_void_array((void ***)&argv);
		argv = set_argv(d, new_prg);
	}
	child_pid = fork();
	if (child_pid == -1)
		return (perror("fork"), -1);
	if (child_pid == 0)
		return (handle_child(d, new_prg, argv));
	return (free(new_prg), handle_parent(d, child_pid));
}
