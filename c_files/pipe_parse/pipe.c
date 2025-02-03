/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:22:17 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/03 18:35:20 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	handle_child_pipe(t_data *d, t_token *cmd, int pipefd[2])
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	handle_command_token(d, cmd);
	close_redir_stream(d);
	custom_exit(d, NULL, NULL, EXIT_SUCCESS);
}

int	handle_parent(int child_pid, int pipefd[2])
{
	int	wait_status;

	setup_signal(1, 0);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
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
	node = node->next;
	while (node)
	{
		if (node->type == tk_command || node->type == tk_exec || \
			node->type == tk_pipe)
			break ;
		node = node->next;
	}
	if (node && node->type == tk_pipe)
		node = node->next;
	return (node);
}

t_token	*execute_pipe(t_data *d, t_token *cmd)
{
	int	pipefd[2];
	int	pid;

	if (pipe(pipefd) == -1)
		custom_exit(d, "pipe failed", NULL, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		custom_exit(d, "pipe fork failed", NULL, EXIT_FAILURE);
	if (pid == 0)
		handle_child_pipe(d, cmd, pipefd);
	else
		d->last_exit_status = handle_parent(pid, pipefd);
	return (update_token_index(cmd));
}

t_token	*handle_pipe(t_data *d, t_token *cmd)
{
	int	original_stdin;

	original_stdin = dup(STDIN_FILENO);
	while (should_call_pipe(cmd))
		cmd = execute_pipe(d, cmd);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
	return (cmd);
}

int	should_call_pipe(t_token *node)
{
	node = node->next;
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
