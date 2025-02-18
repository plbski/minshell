/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_substitute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:44:39 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/17 23:20:31 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

void	handle_child(t_data *d, char *value, int *pipefd)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	exec_input(d, value);
	free(value);
	custom_exit(d, NULL, NULL, EXIT_CHILD);
}

char	*get_cmd_subst(t_data *d, char *str, int *i, char *ret_cmd)
{
	char	*par_value;
	int		status;
	int		pid;
	int		pipefd[2];

	*i += 2;
	par_value = copy_until_char(d, str, i, ")");
	if (pipe(pipefd) == -1)
		custom_exit(d, "pipe in cmdsubstr", NULL, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		custom_exit(d, "fork in cmdsubstr", NULL, EXIT_FAILURE);
	if (pid == 0)
		handle_child(d, par_value, pipefd);
	waitpid(pid, &status, 0);
	close(pipefd[1]);
	setstr(d, &ret_cmd, get_fd_content(d, pipefd[0]));
	close(pipefd[0]);
	if (ret_cmd[ft_strlen(ret_cmd) - 1] == '\n')
		ret_cmd[ft_strlen(ret_cmd) - 1] = '\0';
	while (str[*i] && str[*i] != ')')
		(*i)++;
	return (ret_cmd);
}
