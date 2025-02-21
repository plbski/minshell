/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:22:17 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/21 01:08:11 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static int	cleanup(int or_std, int **fds, int *pids, int pipes_count)
{
	int	i;
	int	status;
	int	exit_st;

	exit_st = 0;
	i = -1;
	while (++i < pipes_count)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		free(fds[i]);
	}
	free(fds);
	i = -1;
	while (++i < pipes_count)
		waitpid(pids[i], NULL, 0);
	if (waitpid(pids[i], &status, 0) != -1)
	{
		if (WIFEXITED(status))
			exit_st = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_st = 128 + WTERMSIG(status);
	}
	return (close(or_std), dup2(or_std, STDIN_FILENO), close(or_std), exit_st);
}

static void	execute_cmd(t_data *d, t_token *cmd, int *fd_in, int *fd_out)
{
	d->fork_child++;
	if (fd_in)
	{
		dup2(fd_in[0], STDIN_FILENO);
		close(fd_in[0]);
		close(fd_in[1]);
	}
	if (fd_out)
	{
		dup2(fd_out[1], STDOUT_FILENO);
		close(fd_out[0]);
		close(fd_out[1]);
	}
	update_node_expansion(d, cmd);
	handle_command_token(d, cmd, 1);
}

static void	iterate_pipes(t_data *d, t_token *strt_cmd, int **pfds, int *pids)
{
	int	i;
	int	pipes_len;

	pipes_len = d->var;
	i = -1;
	while (++i <= pipes_len)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			custom_exit(d, "fork", NULL, EXIT_FAILURE);
		if (pids[i] == 0)
		{
			if (i == 0)
				execute_cmd(d, strt_cmd, NULL, pfds[i]);
			else if (i == pipes_len)
				execute_cmd(d, strt_cmd, pfds[i - 1], NULL);
			else
				execute_cmd(d, strt_cmd, pfds[i - 1], pfds[i]);
			custom_exit(d, NULL, NULL, d->last_exit);
		}
		close(pfds[i][1]);
		if (i > 0)
			close(pfds[i - 1][0]);
		strt_cmd = strt_cmd->pipe_out;
	}
}

static void	init_pipes(t_data *d, t_token *strt_cmd, int pipes_len, int i)
{
	int		base_stdin;
	int		**pipe_fds;
	pid_t	*pids;

	pipe_fds = ms_malloc(d, sizeof(int *) * (pipes_len + 1));
	i = -1;
	while (++i < pipes_len + 1)
	{
		pipe_fds[i] = malloc(sizeof(int) * 2);
		if (pipe(pipe_fds[i]) == -1)
			custom_exit(d, "error in pipe_fd", NULL, EXIT_FAILURE);
	}
	pids = ms_malloc(d, sizeof(pid_t) * (pipes_len + 1));
	base_stdin = dup(STDIN_FILENO);
	d->var = pipes_len;
	iterate_pipes(d, strt_cmd, pipe_fds, pids);
	setup_signal(1, 0);
	d->last_exit = cleanup(base_stdin, pipe_fds, pids, pipes_len);
	setup_signal(0, 0);
}

t_token	*pipe_handler(t_data *d, t_token *cmd_in)
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
	if (d->debug_mode)
		printf("%spipe chain started at %s%s\n", PRP_LAV, cmd_in->name, RESET);
	init_pipes(d, cmd_in, pipes_count, -1);
	if (d->debug_mode)
		printf("%spipe chain ended at %s\n%s", PRP_LAV, node->name, RESET);
	node = get_next_token(node, tk_logical, 0);
	if (d->debug_mode && node)
		show_cmd_status(d, node->next);
	return (node);
}
