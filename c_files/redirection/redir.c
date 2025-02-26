/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/26 21:52:59 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static int	handle_redir_out(t_data *d, t_token *cmd, char *arg, char **flags)
{
	int		fd;

	if (!cmd || !cmd->red_arg || !cmd->red_arg->name)
		custom_exit(d, "error in redir in", NULL, EXIT_FAILURE);
	cmd->red_arg = update_node_expansion(d, cmd->red_arg);
	save_stds(d);
	fd = get_fd(d, cmd->red_arg->name, tk_red_out);
	if (fd == -1)
		return (FCT_FAIL);
	if (cmd->redir->rd_fd > 0 && dup2(fd, cmd->redir->rd_fd) == -1)
		custom_exit(d, "dup2 fail handle_redapp", NULL, EXIT_FAILURE);
	else if (cmd->redir->rd_fd == -1 && dup2(fd, STDOUT_FILENO) == -1)
		custom_exit(d, "dup2 fail handle_redout", NULL, EXIT_FAILURE);
	close(fd);
	if (cmd->last_out == cmd->redir)
		d->last_exit = execute_command(d, cmd->name, arg, flags);
	reset_redir(d);
	return (FCT_OK);
}

static int	handle_redir_app(t_data *d, t_token *cmd, char *arg, char **flags)
{
	int		fd;

	if (!cmd || !cmd->red_arg || !cmd->red_arg->name)
		custom_exit(d, "error in redir in", NULL, EXIT_FAILURE);
	cmd->red_arg = update_node_expansion(d, cmd->red_arg);
	save_stds(d);
	fd = get_fd(d, cmd->red_arg->name, tk_red_app);
	if (fd == -1)
		return (FCT_FAIL);
	if (cmd->redir->rd_fd != -1 && dup2(fd, cmd->redir->rd_fd) == -1)
		custom_exit(d, "dup2 fail handle_redapp", NULL, EXIT_FAILURE);
	else if (cmd->redir->rd_fd == -1 && dup2(fd, STDOUT_FILENO) == -1)
		custom_exit(d, "dup2 fail handle_redapp", NULL, EXIT_FAILURE);
	close(fd);
	if (cmd->last_out == cmd->redir)
		d->last_exit = execute_command(d, cmd->name, arg, flags);
	reset_redir(d);
	return (FCT_OK);
}

static int	handle_redir_in(t_data *d, t_token *cmd, char *arg, char **flags)
{
	char	*file_name;
	int		fd;

	if (!cmd || !cmd->red_arg || !cmd->red_arg->name)
		custom_exit(d, "error in redir in", NULL, EXIT_FAILURE);
	cmd->red_arg = update_node_expansion(d, cmd->red_arg);
	file_name = cmd->red_arg->name;
	if (access(file_name, F_OK) == -1)
		return (ft_dprintf(2, "msh: %s: No such file or directory\n", \
			file_name), FCT_FAIL);
	save_stds(d);
	fd = get_fd(d, file_name, tk_red_in);
	if (fd == -1)
		return (FCT_FAIL);
	if (cmd->redir->rd_fd != -1 && dup2(fd, cmd->redir->rd_fd) == -1)
		custom_exit(d, "dup2 fail handle_redapp", NULL, EXIT_FAILURE);
	else if (dup2(fd, STDIN_FILENO) == -1)
		custom_exit(d, "dup2 fail handle_redin", NULL, EXIT_FAILURE);
	close(fd);
	if (cmd->last_in == cmd->redir)
		d->last_exit = execute_command(d, cmd->name, arg, flags);
	reset_redir(d);
	return (FCT_OK);
}

static int	handle_heredoc(t_data *d, t_token *cmd, char *arg, char **flags)
{
	int		fd;
	char	*file_name;

	save_stds(d);
	if (!cmd || !cmd->red_arg || !cmd->red_arg->cnt_hered)
		custom_exit(d, "error in hered", NULL, EXIT_FAILURE);
	file_name = ms_strjoin(d, d->start_wd, "/heredoc_output");
	fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		custom_exit(d, "error in redir heredoc", NULL, EXIT_FAILURE);
	write(fd, cmd->red_arg->cnt_hered, ft_strlen(cmd->red_arg->cnt_hered));
	close(fd);
	fd = get_fd(d, file_name, tk_red_in);
	if (fd == -1)
		custom_exit(d, "error heredoc", NULL, EXIT_FAILURE);
	if (dup2(fd, STDIN_FILENO) == -1)
		custom_exit(d, "dup2 fail handle_redin", NULL, EXIT_FAILURE);
	close(fd);
	if (cmd->last_in == cmd->redir)
		d->last_exit = execute_command(d, cmd->name, arg, flags);
	unlink(file_name);
	free(file_name);
	reset_redir(d);
	return (FCT_OK);
}

t_token	*handle_redir_cmd(t_data *d, t_token *cmd, char *arg, char **flags)
{
	t_token		*next;
	char		name[999];

	next = get_last_arg(cmd);
	if (next)
		next = next->next;
	if (cmd->redir->type != tk_hered)
	{
		ft_strlcpy(name, cmd->red_arg->name, 999);
		cmd->red_arg = update_node_expansion(d, cmd->red_arg);
		if (!cmd->red_arg || !cmd->red_arg->name)
			return (ft_dprintf(2, "msh: %s: ambiguous redirect\n", name), \
				d->last_exit = FCT_FAIL, next);
	}
	if (cmd->redir->type == tk_hered)
		d->var = handle_heredoc(d, cmd, arg, flags);
	else if (cmd->redir->type == tk_red_app)
		d->var = handle_redir_app(d, cmd, arg, flags);
	else if (cmd->redir->type == tk_red_out)
		d->var = handle_redir_out(d, cmd, arg, flags);
	else
		d->var = handle_redir_in(d, cmd, arg, flags);
	if (d->var != FCT_OK)
		d->last_exit = d->var;
	return (d->var = 0, next);
}
