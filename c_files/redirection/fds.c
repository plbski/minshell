/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 02:20:38 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/16 15:07:26 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	get_fd(t_data *d, char *file_path, t_tktype r_type)
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

void	save_stds(t_data *d)
{
	d->saved_stdin = dup(STDIN_FILENO);
	d->saved_stdout = dup(STDOUT_FILENO);
	if (d->saved_stdin == -1 || d->saved_stdout == -1)
		custom_exit(d, "Failed to save original fd", NULL, EXIT_FAILURE);
}

void	reset_redir(t_data *d)
{
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

void	restore_fds(t_data *d)
{
	if (d->base_stdin != -1)
	{
		if (dup2(d->base_stdin, STDIN_FILENO) == -1)
			custom_exit(d, "Failed to restore stdin", NULL, EXIT_FAILURE);
		close(d->base_stdin);
		d->base_stdin = -1;
	}
	if (d->base_stdout != -1)
	{
		if (dup2(d->base_stdout, STDIN_FILENO) == -1)
			custom_exit(d, "Failed to restore stdout", NULL, EXIT_FAILURE);
		close(d->base_stdout);
		d->base_stdout = -1;
	}
}
