/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plbuet <plbuet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/06 20:10:09 by plbuet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	close_redir_stream(t_data *d)
{
	if (dup2(1, STDIN_FILENO) == -1)
		custom_exit(d, "erreur dup2", NULL, EXIT_FAILURE);
	if (dup2(0, STDOUT_FILENO) == -1)
		custom_exit(d, "erreur dup2", NULL, EXIT_FAILURE);
	if (d->fd)
		close(d->fd);
	d->fd = 0;
}

static int	get_fd(t_data *d, char *file_path, t_toktype r_type)
{
	int	fd;

	if (r_type == tk_red_app)
		fd = open(file_path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (r_type == tk_red_out)
		fd = open(file_path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(file_path, O_RDONLY);
	if (fd == -1)
		custom_exit(d, "erreur dup2", NULL, EXIT_FAILURE);
	return (fd);
}

void	create_file(t_data *d, char *file_name, t_toktype r_type)
{
	char	*path;
	int		fd;
	int		dup_target;

	if (d->debug_mode)
		printf("created %s for %d\n", file_name, r_type);
	fd = 0;
	if (!file_name)
		custom_exit(d, "error in redir", NULL, EXIT_FAILURE);
	path = ft_str_mega_join(d->cwd, "/", file_name, NULL);
	if (!path)
		custom_exit(d, "error in redir", NULL, EXIT_FAILURE);
	fd = get_fd(d, path, r_type);
	free(path);
	if ((r_type == tk_red_app || r_type == tk_red_out))
		dup_target = STDOUT_FILENO;
	else
		dup_target = STDIN_FILENO;
	if (dup2(fd, dup_target) == -1)
		custom_exit(d, "erreur dup2", NULL, EXIT_FAILURE);
	if (fd)
		d->fd = fd;
}

t_token	*handle_redir_token(t_data *d, t_token *redir_node, t_toktype type)
{
	t_token		*after_redir;
	t_token		*before_redir;
	char		*return_content;

	after_redir = redir_node->next;
	before_redir = redir_node->prv;
	if (type == tk_hered)
	{
		return_content = heredoc(after_redir->name, d, "heredoc> ", 0);
		safe_free(return_content);
	}
	else if (!after_redir || ! before_redir)
		custom_exit(d, "Error in redir tokens", NULL, EXIT_FAILURE);
	if (type == tk_red_out || type == tk_red_app)
		create_file(d, after_redir->name, type);
	else if (type == tk_red_in)
		create_file(d, after_redir->name, tk_red_in);
	if (after_redir)
		return (after_redir->next);
	return (after_redir);
}
