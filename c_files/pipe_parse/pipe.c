/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:22:17 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/07 16:03:56 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static void	handle_child(t_data *d, t_token *cmd, int *fd_in, int *fd_out)
{
	if (fd_in)
	{
		dup2(fd_in[0], STDIN_FILENO);
		close(fd_in[0]);
	}
	if (fd_out)
	{
		dup2(fd_out[1], STDOUT_FILENO);
		close(fd_out[1]);
	}
	handle_command_token(d, cmd, 1);
	custom_exit(d, NULL, NULL, EXIT_CHILD);
}

static void	handle_parent(int or_stdin, int **fds, int *pids, int pipes_count)
{
	int	i;

	setup_signal(1, 0);
	i = -1;
	while (++i <= pipes_count)
	{
		close(fds[i][0]);
		close(fds[i][1]);
	}
	i = -1;
	while (++i < pipes_count)
		waitpid(pids[i], NULL, 0);
	setup_signal(0, 0);
	dup2(or_stdin, STDIN_FILENO);
	close(or_stdin);
}

static int	**ini_pipefds(t_data *d, int pipes_amount, int **pipe_fds)
{
	int	i;

	i = -1;
	pipe_fds = ms_malloc(d, sizeof(int *) * pipes_amount);
	while (++i <= pipes_amount)
	{
		pipe_fds[i] = malloc(sizeof(int) * 2);
		if (pipe(pipe_fds[i]) == -1)
			custom_exit(d, "error in pipe_fd", NULL, EXIT_FAILURE);
	}
	return(pipe_fds);
}

static void	execute_pipes(t_data *d, t_token *start_cmd, int pipes_amount)
{
	int		base_stdin;
	int		**pipe_fds;
	pid_t	*pids;
	int		i;

	pipe_fds = ini_pipefds(d, pipes_amount, NULL);
	pids = ms_malloc(d, sizeof(pid_t) * (pipes_amount + 1));
	base_stdin = dup(STDIN_FILENO);
	i = -1;
	while (++i <= pipes_amount)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			custom_exit(d, "fork", NULL, EXIT_FAILURE);
		if (pids[i] == 0)
		{
			if (i == 0)
				handle_child(d, start_cmd, NULL, pipe_fds[i]);
			else if (i == pipes_amount)
				handle_child(d, start_cmd, pipe_fds[i - 1], NULL);
			else
				handle_child(d, start_cmd, pipe_fds[i - 1], pipe_fds[i]);
		}
		start_cmd = start_cmd->pipe_out;
	}
	handle_parent(base_stdin, pipe_fds, pids, pipes_amount);
}

t_token	*handle_pipe(t_data *d, t_token *cmd_in)
{
	t_token		*node;
	int			pipes_count;

	pipes_count = 0;
	node = cmd_in;
	while (node && node->pipe_out)
	{
		pipes_count++;
		node = node->pipe_out;
	}
	execute_pipes(d, cmd_in, pipes_count);
	if (!node || !node->pipe_out)
		return (NULL);
	return (node->pipe_out->next);
}
