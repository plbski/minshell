/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:22:17 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/24 18:03:38 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"


static void	close_fds_and_free(int **pfds, int *pids, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(pfds[i][0]);
		close(pfds[i][1]);
		free(pfds[i]);
		i++;
	}
	free(pfds);
	free(pids);
}

static int	cleanup(int **fds, int *pids, int pipes_count)
{
	int	i;
	int	status;
	int	exit_st;

	exit_st = 0;
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
	close_fds_and_free(fds, pids, pipes_count);
	return (exit_st);
}

static void	execute_cmd(t_data *d, t_token *cmd, int *fd_in, int *fd_out)
{
	d->fork_child++;
	if (fd_in)
	{
		close(fd_in[1]); 
		if (dup2(fd_in[0], STDIN_FILENO) == -1)
			custom_exit(d, "dup2", NULL, EXIT_FAILURE);
		close(fd_in[0]);
	}
	if (fd_out)
	{
		close(fd_out[0]);
		if (dup2(fd_out[1], STDOUT_FILENO) == -1)
			custom_exit(d, "dup2", NULL, EXIT_FAILURE);
		close(fd_out[1]);
	}
	cmd = update_node_expansion(d, cmd);
	if (cmd)
	{
		handle_command_token(d, cmd, 1);
		clear_tokens(token_first(cmd));
	}
}

static void	iterate_pipes(t_data *d, t_token *cmd, int **pfds, int *pids)
{
	int		i;
	int		num_cmds;

	num_cmds = d->var + 1;
	i = 0;
	while (i < num_cmds)
	{
		if (i < num_cmds - 1)
		{
			if (pipe(pfds[i]) == -1)
				custom_exit(d, "error in pipe_fd", NULL, EXIT_FAILURE);
		}
		pids[i] = fork();
		if (pids[i] < 0)
			custom_exit(d, "fork", NULL, EXIT_FAILURE);
		if (pids[i] == 0)
		{
			if (i == 0)
			{
				if (num_cmds > 1)
					execute_cmd(d, cmd, NULL, pfds[i]);
				else
					execute_cmd(d, cmd, NULL, NULL);
			}
			else if (i == num_cmds - 1)
				execute_cmd(d, cmd, pfds[i - 1], NULL);
			else
				execute_cmd(d, cmd, pfds[i - 1], pfds[i]);
			custom_exit(d, NULL, NULL, d->last_exit);
		}
		if (i > 0)
		{
			close(pfds[i - 1][0]);
			close(pfds[i - 1][1]);
		}
		cmd = cmd->pipe_out;
		i++;
	}
}

static void	init_pipes(t_data *d, t_token *strt_cmd, int pipes_len, int i)
{
	int		**pipe_fds;
	pid_t	*pids;

	pipe_fds = ms_malloc(d, sizeof(int *) * (pipes_len + 1));
	i = -1;
	while (++i < pipes_len + 1)
		pipe_fds[i] = malloc(sizeof(int) * 2);
	pids = ms_malloc(d, sizeof(pid_t) * (pipes_len + 1));
	d->var = pipes_len;
	iterate_pipes(d, strt_cmd, pipe_fds, pids);
	setup_signal(1, 0);
	d->last_exit = cleanup(pipe_fds, pids, pipes_len);
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
