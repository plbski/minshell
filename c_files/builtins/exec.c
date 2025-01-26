/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:23:52 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/26 12:38:49 by giuliovalen      ###   ########.fr       */
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

int	exec(t_data *d, char *arg, char **flags, int _u __attribute__((unused)))
{
	pid_t		child_pid;
	int			wait_status;

	if (access(arg, F_OK) == -1)
	{
		printf("mshell: %s: No such file or directory\n", arg);
		return (0);
	}
	child_pid = fork();
	if (child_pid == 0)
	{
		increment_shlvl(d);
		update_environ(d);
		execve(arg, &flags, d->environ);
		custom_exit(d, NULL, NULL, EXIT_SUCCESS);
	}
	else
	{
		if (waitpid(child_pid, &wait_status, 0) == -1)
			return (printf("child exited\n"), 0);
		if (WIFEXITED(wait_status))
			return (WEXITSTATUS(wait_status));
	}
	return (1);
}
