/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:19:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/03/04 11:54:48 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

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

void	set_last_redirs(t_data *d, t_token *cmd, char *arg, char **flags)
{
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
}

void	open_residual_files(t_data *d, t_token *cmd, t_token *start_redir)
{
	int	fd;

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
}

t_token	*handle_mult_redirs(t_data *d, t_token *cmd, char *arg, char **flags)
{
	t_token	*start_redir;

	start_redir = cmd->redir;
	save_stds(d);
	select_main_redir(cmd);
	set_last_redirs(d, cmd, arg, flags);
	if (d->var != FCT_FAIL)
		d->last_exit = execute_command(d, cmd->name, arg, flags);
	reset_redir(d);
	if (access(d->heredoc_wd, F_OK) != -1)
		unlink(d->heredoc_wd);
	open_residual_files(d, cmd, start_redir);
	return (get_last_arg(cmd->red_arg));
}
