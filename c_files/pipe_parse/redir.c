/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/12 18:32:55 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	save_original_fds(t_data *d)
{
	d->saved_stdin = dup(STDIN_FILENO);
	d->saved_stdout = dup(STDOUT_FILENO);
	if (d->saved_stdin == -1 || d->saved_stdout == -1)
		custom_exit(d, "Failed to save original fd", NULL, EXIT_FAILURE);
}

void	close_redir_stream(t_data *d)
{
	if (d->fd >= 0)
		close(d->fd);
	d->fd = -1;
	if (d->saved_stdin == -1 && d->saved_stdout == -1)
		return ;
	if (d->saved_stdin != -1 && dup2(d->saved_stdin, STDIN_FILENO) == -1)
		custom_exit(d, "Failed to restore STDIN", NULL, EXIT_FAILURE);
	if (d->saved_stdout != -1 && dup2(d->saved_stdout, STDOUT_FILENO) == -1)
		custom_exit(d, "Failed to restore STDOUT", NULL, EXIT_FAILURE);
	if (d->saved_stdin != -1)
		close(d->saved_stdin);
	if (d->saved_stdout != -1)
		close(d->saved_stdout);
	d->saved_stdin = -1;
	d->saved_stdout = -1;
}

int	get_fd(t_data *d, char *file_path, t_tktype r_type)
{
	int	fd;

	printf("%s\n", file_path);
	if (r_type == tk_red_app)
		fd = open(file_path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (r_type == tk_red_out)
		fd = open(file_path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (r_type == tk_red_in)
		fd = open(file_path, O_RDONLY);
	else
		fd = open(file_path, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		custom_exit(d, "erreur open files", NULL, EXIT_FAILURE);
	return (fd);
}

int	create_file(t_data *d, char *file_name, t_tktype r_type)
{
	char	*path;
	int		dup_target;

	if (access(file_name, F_OK) == -1 && r_type == tk_red_in)
		return (printf("msh: %s: No such file or directory\n", file_name), 0);
	save_original_fds(d);
	d->fd = 0;
	if (!file_name)
		custom_exit(d, "error in redir", NULL, EXIT_FAILURE);
	path = ft_str_mega_join(d->cwd, "/", file_name, NULL);
	if (!path)
		custom_exit(d, "error in redir", NULL, EXIT_FAILURE);
	d->fd = get_fd(d, path, r_type);
	free(path);
	if ((r_type == tk_red_app || r_type == tk_red_out))
		dup_target = STDOUT_FILENO;
	else if (r_type == tk_red_in)
		dup_target = STDIN_FILENO;
	else
		return (1);
	if (dup2(d->fd, dup_target) == -1)
		custom_exit(d, "erreur dup2", NULL, EXIT_FAILURE);
	if (d->fd >= 0)
		close(d->fd);
	return (1);
}

t_token	*handle_redir(t_data *d, t_token *redir, \
		t_token *tok_after, t_tktype type)
{
	t_token		*before_redir;

	before_redir = redir->prv;
	if (type == tk_hered)
	{
		create_file(d,"ressource/.heredoc", tk_hered);
		ft_heredoc(tok_after->name, d, "heredoc> ");
	}
	else if (!tok_after || ! before_redir)
		custom_exit(d, "Error in redir tokens", NULL, EXIT_FAILURE);
	if (type == tk_red_out || type == tk_red_app)
	{
		if (before_redir && before_redir->pipe_out)
			handle_command_token(d, before_redir, 0);
		create_file(d, tok_after->name, type);
	}
	else if (type == tk_red_in)
		create_file(d, tok_after->name, tk_red_in);
	if (tok_after)
		return (tok_after->next);
	return (tok_after);
}