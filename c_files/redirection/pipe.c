/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:22:17 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/26 18:40:42 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static void	select_right_redir(t_data *d, int i, int **pfds)
{
	d->fork_child++;
	if (i == 0 && (d->var + 1) > 1)
		redirect_pipe_stds(d, NULL, pfds[i]);
	else if (i == 0)
		redirect_pipe_stds(d, NULL, NULL);
	else if (i == d->var)
		redirect_pipe_stds(d, pfds[i - 1], NULL);
	else
		redirect_pipe_stds(d, pfds[i - 1], pfds[i]);
}

static void	iterate_pipes(t_data *d, t_token *cmd, int **pfds, int *pids)
{
	int		i;

	i = -1;
	while (++i < d->var + 1)
	{
		if (i < d->var && pipe(pfds[i]) == -1)
			custom_exit(d, "error in pipe_fd", NULL, EXIT_FAILURE);
		pids[i] = fork();
		if (pids[i] < 0)
			custom_exit(d, "fork", NULL, EXIT_FAILURE);
		if (pids[i] == 0)
		{
			select_right_redir(d, i, pfds);
			free_pfds_and_pids(pfds, pids, d->var + 1);
			execute_cmd(d, cmd);
			custom_exit(d, NULL, NULL, d->last_exit);
		}
		cmd = cmd->pipe_out;
		if (i <= 0)
			continue ;
		close(pfds[i - 1][0]);
		close(pfds[i - 1][1]);
	}
}

static void	init_pipes(t_data *d, t_token *strt_cmd, int pipes_len, int i)
{
	int		**pipe_fds;
	pid_t	*pids;

	pipe_fds = ms_malloc(d, sizeof(int *) * (pipes_len + 1));
	i = -1;
	while (++i < pipes_len + 1)
		pipe_fds[i] = ms_malloc(d, sizeof(int) * 2);
	pids = ms_malloc(d, sizeof(pid_t) * (pipes_len + 1));
	d->var = pipes_len;
	iterate_pipes(d, strt_cmd, pipe_fds, pids);
	d->var = 0;
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
