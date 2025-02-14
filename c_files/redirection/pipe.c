/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:22:17 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/14 16:12:38 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static void	cleanup(int or_stdin, int **fds, int *pids, int pipes_count)
{
	int	i;

	setup_signal(1, 0);
	i = -1;
	while (++i < pipes_count)
	{
		close(fds[i][0]);
		close(fds[i][1]);
	}
	free(fds);
	i = -1;
	while (++i <= pipes_count)
		waitpid(pids[i], NULL, 0);
	setup_signal(0, 0);
	dup2(or_stdin, STDIN_FILENO);
	close(or_stdin);
}

static void	execute_cmd(t_data *d, t_token *cmd, int *fd_in, int *fd_out)
{
	int	should_redir;

	update_node_expansion(d, cmd, 0);
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
	if (cmd->redir)
		restore_fds(d);
	should_redir = 1;
	handle_command_token(d, cmd, should_redir);
	custom_exit(d, NULL, NULL, EXIT_CHILD);
}

static int	**init_fds(t_data *d, int pipes_amount)
{
	int	i;
	int	**pipe_fds;

	pipe_fds = ms_malloc(d, sizeof(int *) * (pipes_amount));
	i = -1;
	while (++i < pipes_amount)
	{
		pipe_fds[i] = malloc(sizeof(int) * 2);
		if (pipe(pipe_fds[i]) == -1)
			custom_exit(d, "error in pipe_fd", NULL, EXIT_FAILURE);
	}
	return (pipe_fds);
}

static void	init_pipes(t_data *d, t_token *strt_cmd, int pipes_len, int i)
{
	int		base_stdin;
	int		**pipe_fds;
	pid_t	*pids;

	pipe_fds = init_fds(d, pipes_len);
	pids = ms_malloc(d, sizeof(pid_t) * (pipes_len + 1));
	base_stdin = dup(STDIN_FILENO);
	i = -1;
	while (++i <= pipes_len)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			custom_exit(d, "fork", NULL, EXIT_FAILURE);
		if (pids[i] == 0)
		{
			if (i == 0)
				execute_cmd(d, strt_cmd, NULL, pipe_fds[i]);
			else if (i == pipes_len)
				execute_cmd(d, strt_cmd, pipe_fds[i - 1], NULL);
			else
				execute_cmd(d, strt_cmd, pipe_fds[i - 1], pipe_fds[i]);
		}
		strt_cmd = strt_cmd->pipe_out;
	}
	cleanup(base_stdin, pipe_fds, pids, pipes_len);
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
	init_pipes(d, cmd_in, pipes_count, -1);
	if (d->debug_mode)
		printf("pipe chain ended at %s\n", node->name);
	node = get_next_token(node, tk_logical, 0);
	if (node && d->debug_mode)
		show_cmd_status(d, node->next);
	else if (d->debug_mode)
		printf("no more tokens.\n");
	return (node);
}
