/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:46:30 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/27 00:32:24 by giuliovalen      ###   ########.fr       */
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

void	select_main_redir(t_token *cmd)
{
	t_token	*last_in;
	t_token	*last_out;
	t_token	*rd;

	last_in = NULL;
	last_out = NULL;
	rd = cmd->redir;
	while (rd)
	{
		if (rd->type == tk_hered)
			last_in = rd;
		else if (rd->type == tk_red_in && \
			(!last_in || last_in->type != tk_hered))
			last_in = rd;
		else if (rd->type == tk_red_app || rd->type == tk_red_out)
			last_out = rd;
		rd = rd->redir;
	}
	cmd->last_in = last_in;
	cmd->last_out = last_out;
}

t_token	*handle_mult_redirs(t_data *d, t_token *cmd, char *arg, char **flags)
{
	int		fd;
	t_token	*start_redir;

	save_stds(d);
	start_redir = cmd->redir;
	select_main_redir(cmd);
	if (cmd->last_in)
	{
		cmd->redir = cmd->last_in;
		cmd->red_arg = cmd->last_in->next;
		handle_redir_cmd(d, cmd, arg, flags);
	}
	if (cmd->last_out)
	{
		cmd->redir = cmd->last_out;
		cmd->red_arg = cmd->last_out->next;
		handle_redir_cmd(d, cmd, arg, flags);
	}
	d->last_exit = execute_command(d, cmd->name, arg, flags);
	reset_redir(d);
	if (access(d->heredoc_wd, F_OK) != -1)
		unlink(d->heredoc_wd);
	cmd->redir = start_redir;
	while (cmd->redir)
	{
		cmd->red_arg = cmd->redir->next;
		if ((cmd->last_out && cmd->redir == cmd->last_out) || \
			(cmd->last_in && cmd->redir == cmd->last_in))
		{
			cmd->redir = cmd->redir->redir;
			continue ;
		}
		if (cmd->redir->type == tk_red_out || cmd->redir->type == tk_red_app)
		{
			fd = get_fd(d, cmd->red_arg->name, cmd->redir->type);
			close(fd);
		}
		cmd->redir = cmd->redir->redir;
	}
	return (get_last_arg(cmd->red_arg));
}
