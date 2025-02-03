/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plbuet <plbuet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:22:17 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/03 14:53:24 by plbuet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	execute_pipe(t_data *d, char *prompt)
{
	int		i;
	char	**cmd;
	int		prev_fd;
	int		pipe_fd[2];
	pid_t	pid;

	i = 0;
	prev_fd = -1;
	cmd = ft_split(prompt, '|');
	while (cmd[i])
	{
		if (cmd[i + 1] != NULL && pipe(pipe_fd) == -1)
			custom_exit(d, "erreur pipe", NULL, EXIT_FAILURE);
		pid = fork();
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			} //lire depuis l entre du precedent pipe
			if (cmd[i + 1] != NULL)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
				close(pipe_fd[0]);
			}
			handle_splits(d, redir(d, cmd[i]));
			exit(0);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd[i + 1] != NULL)
			{
				close(pipe_fd[1]);
				prev_fd = pipe_fd[0];
			}
		}
		i ++;
	}
	while (wait(NULL) >0);
	free(cmd);
}
