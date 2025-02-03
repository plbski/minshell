/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:22:17 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/03 17:17:33 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

t_token	*handle_child_pipe(t_data *d, t_token *cmd)
{
	return (handle_command_token(d, cmd));
}

int	handle_parent(int child_pid)
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

t_token	*update_token_index(t_token *node)
{
	while (node)
	{
		if (!node->next || (node->next->type != tk_argument && node->next->type != tk_pipe))
			break ;
		node = node->next;
	}
	return (node);
}

t_token	*execute_pipe(t_data *d, t_token *cmd)
{
	d->pipefd = fork();
	if (d->pipefd == -1)
		custom_exit(d, "pipe fork failed", NULL, EXIT_FAILURE);
	if (d->pipefd == 0)
		handle_child_pipe(d, cmd);
	else
		d->last_exit_status = handle_parent(d->pipefd);
	cmd = update_token_index(cmd);
	return (cmd);
}

t_token	*handle_pipe(t_data *d, t_token *cmd)
{
	while (should_call_pipe(cmd))
		cmd = execute_pipe(d, cmd);
	close(d->pipefd);
	return (cmd);
}

int	should_call_pipe(t_token *node)
{
	while (node)
	{
		if (node->type == tk_command || node->type == tk_exec)
			return (0);
		if (node->type == tk_pipe)
			return (1);
		node = node->next;
	}
	return (0);
}
