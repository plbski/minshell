/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:23:52 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/26 18:15:24 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	increment_shlvl(t_data *d)
{
	t_dblist	*element;
	char		*new_lvl;

	new_lvl = ft_itoa(d->shlvl + 1);
	if (!new_lvl)
		return (custom_exit(d, "SHLVL alloc failed", NULL, EXIT_FAILURE));
	element = get_dblst_at_key(d->env_list, "SHLVL");
	if (!element)
		return (0);
	if (!set_key_value(d, d->env_list, "SHLVL", new_lvl))
		return (custom_exit(d, "SHLVL not in env", NULL, EXIT_FAILURE));
	free(new_lvl);
	return (1);
}

void	set_argv(t_data *d, char *prog_name, char ***argv)
{
	if (*argv)
		free_void_array((void ***)argv);
	*argv = malloc(sizeof(char *) * 2);
	if (!*argv)
		custom_exit(d, "Exec argv error", NULL, EXIT_FAILURE);
	*argv[0] = ft_strdup(prog_name);
	if (!*argv[0])
		custom_exit(d, "Exec argv error", NULL, EXIT_FAILURE);
	*argv[1] = NULL;
}

int	handle_child_process(t_data *d, char *program, char **argv)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	increment_shlvl(d);
	update_environ(d);
	execve(program, argv, d->environ);
	perror("execve");
	exit(EXIT_FAILURE);
	return (0);
}

int	handle_parent_process(pid_t child_pid)
{
	int			wait_status;

	setup_signal(1);
	if (waitpid(child_pid, &wait_status, 0) == -1)
	{
		printf("\n");
		return (0);
	}
	printf("\n");
	setup_signal(0);
	if (WIFEXITED(wait_status))
		return (WEXITSTATUS(wait_status));
	return (wait_status);
}

int	exec(t_data *d, char *program, char **argv, int u _UNUSED)
{
	pid_t		child_pid;

	if (!program)
		return (0);
	if (!argv || !argv[0])
		set_argv(d, program, &argv);
	if (access(program, F_OK) == -1)
		return (printf("msh: %s: No such file or directory\n", program), 0);
	if (access(program, X_OK) == -1)
		return (printf("msh: %s: Permission denied\n", program), 0);
	child_pid = fork();
	if (child_pid == 0)
		return (handle_child_process(d, program, argv));
	else
		return (handle_parent_process(child_pid));
}
