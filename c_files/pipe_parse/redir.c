/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/31 09:02:25 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	get_fd(t_data *d, char *file_path, t_toktype r_type)
{
	int	fd;

	if (r_type == tk_redir_app)
		fd = open(file_path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (r_type == tk_redir_out)
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

	printf("%s %d\n", file_name, r_type);
	fd = 0;
	if (!file_name)
		custom_exit(d, "error in redir", NULL, EXIT_FAILURE);
	path = ft_str_mega_join(d->cwd, "/", file_name, NULL);
	!path && (custom_exit(d, "error in redir", NULL, EXIT_FAILURE));
	fd = get_fd(d, path, r_type);
	if ((r_type == tk_redir_app || r_type == tk_redir_out))
		dup_target = STDOUT_FILENO;
	else
		dup_target = STDIN_FILENO;
	if (dup2(fd, dup_target) == -1)
		custom_exit(d, "erreur dup2", NULL, EXIT_FAILURE);
	fd && (d->fd = fd);
}

t_token	*handle_redir(t_data *d, t_token *redir_node, t_toktype type)
{
	t_token		*after_redir;
	t_token		*before_redir;

	after_redir = redir_node->next;
	before_redir = redir_node->prv;
	if (type == tk_heredox)
	{
		heredoc(after_redir->name, d, "heredoc> ", 0);
		return (after_redir);
	}
	else if (!after_redir || ! before_redir)
		custom_exit(d, "Error in redir tokens", NULL, EXIT_FAILURE);
	if (type == tk_redir_out || type == tk_redir_app)
		create_file(d, after_redir->name, type);
	else
		create_file(d, before_redir->name, tk_redir_in);
	return (after_redir->next);
}
