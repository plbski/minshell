/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:46:30 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/27 16:19:34 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

void	redirect_pipe_stds(t_data *d, int *fd_in, int *fd_out)
{
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
}

void	execute_cmd(t_data *d, t_token *cmd)
{
	cmd = update_node_expansion(d, cmd);
	if (cmd && cmd->type == tk_cmd)
		handle_command_token(d, cmd, 1);
	clear_tokens(d->input_tokens);
	d->input_tokens = NULL;
	cmd = NULL;
}

void	free_pfds_and_pids(int **pfds, int *pids, int count)
{
	int	i;

	i = 0;
	while (pfds && i < count)
	{
		free(pfds[i]);
		i++;
	}
	if (pfds)
		free(pfds);
	if (pids)
		free(pids);
}

int	cleanup(int **fds, int *pids, int pipes_count)
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
	free_pfds_and_pids(fds, pids, pipes_count + 1);
	return (exit_st);
}
