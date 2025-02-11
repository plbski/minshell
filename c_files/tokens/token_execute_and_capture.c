/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_execute_and_capture.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:37:20 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/11 18:27:32 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	*get_fd_content(t_data *d, int fd)
{
	char	*line;
	char	*full;
	char	*tmp;

	full = ms_strdup(d, "");
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strjoin(full, line);
		free(full);
		full = tmp;
		free(line);
		line = get_next_line(fd);
	}
	return (full);
}

t_token	*redirect_pipe(t_data *d, t_token *nxt, int pipefd[2], int redir)
{
	int		fd;
	char	*output;

	output = get_fd_content(d, pipefd[0]);
	if (!output)
	{
		if (d->debug_mode)
			printf("no output found for redir\n");
		return (nxt);
	}
	while (nxt && nxt->type == tk_argument)
	{
		fd = get_fd(d, nxt->name, redir);
		if (fd >= 0)
		{
			write(fd, output, ft_strlen(output));
			close(fd);
		}
		nxt = nxt->next;
	}
	free(output);
	return (nxt);
}

t_token	*get_after_red(t_data *d, t_token *cmd)
{
	t_token	*next;

	next = cmd;
	while (next && next->type != tk_red_out && next->type != tk_red_app)
		next = next->next;
	if (!next || !next->next)
		custom_exit(d, "exec redir error: no after redir", NULL, EXIT_FAILURE);
	return (next->next);
}

t_token	*skip_type(t_token *tok, t_tktype type_to_skip)
{
	while (tok && tok->type == type_to_skip)
		tok = tok->next;
	return (tok);
}

t_token	*exec_cmd_with_redir(t_data *d, t_token *cmd, char *arg, char **flags)
{
	pid_t	pid;
	int		pipefd[2];
	t_token	*after_red;
	int		ret_value;

	after_red = get_after_red(d, cmd);
	if (pipe(pipefd) == -1)
		custom_exit(d, "Pipe creation failed", NULL, EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		ret_value = execute_command(d, cmd->name, arg, flags);
		custom_exit(d, "null", NULL, ret_value);
	}
	close(pipefd[1]);
	d->last_exit_st = handle_parent_process(pid);
	if (d->last_exit_st == FCT_SUCCESS)
		after_red = redirect_pipe(d, after_red, pipefd, after_red->prv->type);
	else
		after_red = skip_type(after_red, tk_argument);
	close(pipefd[0]);
	return (after_red);
}
