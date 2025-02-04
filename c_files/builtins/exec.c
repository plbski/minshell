/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:23:52 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/04 09:21:51 by giuliovalen      ###   ########.fr       */
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

static char	**set_argv(t_data *d, char *prog_name)
{
	char	**new_argv;

	new_argv = malloc(sizeof(char *) * 2);
	if (!new_argv)
		custom_exit(d, "Exec argv error", NULL, EXIT_FAILURE);
	new_argv[0] = ms_strdup(d, prog_name);
	new_argv[1] = NULL;
	return (new_argv);
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

int	exec(t_data *d, char *program, char **argv, int u __attribute__((unused)))
{
	pid_t		child_pid;

	if (!argv || !argv[0])
	{
		free_void_array((void ***)&argv);
		argv = set_argv(d, program);
	}
	if (access(program, F_OK) == -1)
	{
		printf("msh: exec: %s:not found\n", program);
		return (FCT_FAIL);
	}
	if (access(program, X_OK) == -1)
	{
		printf("msh: %s: Permission denied\n", program);
		return (FCT_FAIL);
	}
	child_pid = fork();
	if (child_pid == 0)
		return (handle_child_process(d, program, argv));
	else
	{
		d->last_exit_status = handle_parent_process(child_pid);
		printf("\n");
		return (FCT_SUCCESS);
	}
}
