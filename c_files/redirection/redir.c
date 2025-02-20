/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/21 00:08:47 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

void	handle_redir_out(t_data *d, t_token *cmd, char *arg, char **flags)
{
	char	*file_name;
	char	*path;
	int		fd;

	if (!cmd || !cmd->red_arg || !cmd->red_arg->name)
		custom_exit(d, "error in redir in", NULL, EXIT_FAILURE);
	file_name = cmd->red_arg->name;
	save_stds(d);
	path = ft_megajoin(d->cwd, "/", file_name, NULL);
	if (!path)
		custom_exit(d, "error in redir", NULL, EXIT_FAILURE);
	fd = get_fd(d, path, tk_red_out);
	free(path);
	if (fd == -1)
		return ;
	if (dup2(fd, STDOUT_FILENO) == -1)
		custom_exit(d, "dup2 fail handle_redout", NULL, EXIT_FAILURE);
	close(fd);
	d->last_exit = execute_command(d, cmd->name, arg, flags);
	reset_redir(d);
}

void	handle_redir_app(t_data *d, t_token *cmd, char *arg, char **flags)
{
	char	*file_name;
	char	*path;
	int		fd;

	if (!cmd || !cmd->red_arg || !cmd->red_arg->name)
		custom_exit(d, "error in redir in", NULL, EXIT_FAILURE);
	update_node_expansion(d, cmd->red_arg);
	file_name = cmd->red_arg->name;
	save_stds(d);
	path = ft_megajoin(d->cwd, "/", file_name, NULL);
	if (!path)
		custom_exit(d, "error in redir", NULL, EXIT_FAILURE);
	fd = get_fd(d, path, tk_red_app);
	free(path);
	if (fd == -1)
		return ;
	if (dup2(fd, STDOUT_FILENO) == -1)
		custom_exit(d, "dup2 fail handle_redapp", NULL, EXIT_FAILURE);
	close(fd);
	d->last_exit = execute_command(d, cmd->name, arg, flags);
	reset_redir(d);
}

void	handle_redir_in(t_data *d, t_token *cmd, char *arg, char **flags)
{
	char	*file_name;
	int		fd;

	if (!cmd || !cmd->red_arg || !cmd->red_arg->name)
		custom_exit(d, "error in redir in", NULL, EXIT_FAILURE);
	file_name = cmd->red_arg->name;
	if (access(file_name, F_OK) == -1)
	{
		printf("msh: %s: No such file or directory\n", file_name);
		d->last_exit = FCT_FAIL;
		return ;
	}
	save_stds(d);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return ;
	if (dup2(fd, STDIN_FILENO) == -1)
		custom_exit(d, "dup2 fail handle_redin", NULL, EXIT_FAILURE);
	d->last_exit = execute_command(d, cmd->name, arg, flags);
	reset_redir(d);
}

void	handle_redir_heredoc(t_data *d, t_token *hered_arg)
{
	if (d->heredocfd != -1)
	{
		printf("msh: write error: Broken pipe");
		close(d->heredocfd);
	}
	if (!hered_arg)
		custom_exit(d, "error in heredoc", NULL, EXIT_FAILURE);
	if (hered_arg)
		d->heredocfd = ft_heredoc(hered_arg->name, d, "heredoc> ");
}

t_token	*handle_redir_cmd(t_data *d, t_token *cmd, char *arg, char **flags)
{
	t_token		*next;
	char		name[999];

	next = get_last_arg(cmd);
	if (next)
		next = next->next;
	if (!cmd->red_arg->name)
		return (next);
	if (cmd->redir->type != tk_hered)
	{
		ft_strlcpy(name, cmd->red_arg->name, 999);
		update_node_expansion(d, cmd->red_arg);
		if (!cmd->red_arg->name)
			return (ft_dprintf(2, "msh: %s: ambiguous redirect\n", name), next);
	}
	if (cmd->redir->type == tk_hered)
		handle_redir_heredoc(d, cmd->redir->next);
	else if (cmd->redir->type == tk_red_app)
		handle_redir_app(d, cmd, arg, flags);
	else if (cmd->redir->type == tk_red_out)
		handle_redir_out(d, cmd, arg, flags);
	else if (cmd->redir->type == tk_red_in)
		handle_redir_in(d, cmd, arg, flags);
	return (next);
}
