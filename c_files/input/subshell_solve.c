/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_solve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 01:39:10 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/26 18:39:36 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static void	handle_sbsh_in_child(t_data *d, int fd, t_token *start)
{
	d->fork_child++;
	dup2(fd, STDIN_FILENO);
	close(fd);
	iterate_tokens(d, start);
	custom_exit(d, NULL, NULL, EXIT_CHILD);
}

static int	solve_subsh_in(t_data *d, t_token *start, t_token *rd)
{
	int		fd;
	int		pid;
	int		status;

	if (!rd->next || !rd->next->name)
		custom_exit(d, "No name in subhin\n", NULL, EXIT_FAILURE);
	if (rd->type == tk_red_in)
	{
		if (access(rd->next->name, F_OK) == -1)
		{
			ft_dprintf(2, "msh: %s: No file or dir\n", rd->next->name);
			return (0);
		}
		fd = open(rd->next->name, O_RDONLY);
	}
	else
		return (FCT_FAIL);
	if (fd == -1)
		custom_exit(d, "fd read file in subsh_in", NULL, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		custom_exit(d, "fork in subshell inp", NULL, EXIT_FAILURE);
	if (pid == 0)
		handle_sbsh_in_child(d, fd, start);
	return (waitpid(pid, &status, 0), close(fd), 0);
}

static char	*get_subsh_output(t_data *d, t_token *start, int rd_fd)
{
	int		pipefd[2];
	int		pid;
	int		status;
	char	*ret;

	ret = NULL;
	if (pipe(pipefd) == -1)
		custom_exit(d, "pipe in subshell", NULL, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		custom_exit(d, "fork in subshell", NULL, EXIT_FAILURE);
	if (pid == 0)
	{
		d->fork_child++;
		close(pipefd[0]);
		dup2(pipefd[1], rd_fd);
		close(pipefd[1]);
		iterate_tokens(d, start);
		custom_exit(d, NULL, NULL, EXIT_CHILD);
	}
	waitpid(pid, &status, 0);
	close(pipefd[1]);
	setstr(d, &ret, get_fd_content(d, pipefd[0]));
	return (close(pipefd[0]), ret);
}

static t_token	*get_subsh_out(t_data *d, t_token *start, t_token *redir)
{
	t_token	*cmd;
	t_token	*arg;
	char	*output;
	t_token	*node;

	node = start;
	if (d->debug_mode)
		show_tokens_info(d, node, "subsh", -1);
	if (redir->rd_fd <= 0 || redir->rd_fd > 2)
		output = get_subsh_output(d, start, 1);
	else
		output = get_subsh_output(d, start, redir->rd_fd);
	if (!output)
		output = ms_strdup(d, "");
	cmd = new_token("echo", start, tk_cmd, redir->par);
	start->next = cmd;
	arg = new_token(output, cmd, tk_arg, redir->par);
	redir->rd_fd = -1;
	redir->prv = arg;
	arg->next = redir;
	if (redir->type == tk_pipe)
		cmd->pipe_out = redir->next;
	else
		cmd->redir = redir;
	return (free(output), cmd->next = arg, cmd->red_arg = redir->next, cmd);
}

t_token	*solve_subshell(t_data *d, t_token *start)
{
	t_token	*redir;

	if (d->debug_mode)
		printf("redirecting %s subsh; redir:%s arg:%s\n", \
start->name, start->subsh_out->name, start->subsh_out->next->name);
	redir = start->subsh_out;
	if (!redir || (!redir->is_rd && redir->type != tk_pipe))
		return (NULL);
	start->subsh_out->prv->next = NULL;
	start->subsh_out = NULL;
	if (redir->type == tk_hered || redir->type == tk_red_in)
		return (solve_subsh_in(d, start, redir), redir->next);
	return (get_subsh_out(d, start, redir));
}
