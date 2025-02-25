/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:46:30 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/26 00:39:35 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

void	free_pfds_and_pids(int **pfds, int *pids, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(pfds[i]);
		i++;
	}
	free(pfds);
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

t_token	*handle_mult_redirs(t_data *d, t_token *cmd, char *arg, char **flags)
{
	t_token	*last_red_arg;

	while (cmd->redir)
	{
		cmd->red_arg = cmd->redir->next;
		handle_redir_cmd(d, cmd, arg, flags);
		last_red_arg = cmd->red_arg;
		cmd->redir = cmd->redir->redir;
	}
	return (last_red_arg);
}
