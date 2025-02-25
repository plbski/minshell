/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 02:20:38 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/26 00:26:27 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

char	*name_heredoc(t_data *d)
{
	const char	*base = "0123456789ABCDEF";
	pid_t		pid;
	int			j;
	char		tmp[9];
	char		*result;

	j = 8;
	tmp[j] = '\0';
	pid = getpid() + d->fork_child;
	while (j > 0)
	{
		tmp[--j] = base[pid % 16];
		pid /= 16;
	}
	result = ft_strjoin("/ressources/", &tmp[j]);
	if (!result)
		custom_exit(d, "alloc in heredoc\n", NULL, EXIT_FAILURE);
	setstr(d, &result, ft_megajoin(d->start_wd, result, NULL, NULL));
	if (!result)
		custom_exit(d, "alloc in heredoc\n", NULL, EXIT_FAILURE);
	return (result);
}

int	get_fd(t_data *d, char *file_path, t_tktype r_type)
{
	int	fd;

	if (!file_path)
		custom_exit(d, "no path in get_fd", NULL, EXIT_FAILURE);
	if (is_directory(file_path))
	{
		ft_dprintf(2, "msh: %s: Is a directory\n", file_path);
		return (-1);
	}
	if (r_type == tk_red_app)
		fd = open(file_path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (r_type == tk_red_out)
		fd = open(file_path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(2, "msh: %s: Permission denied\n", file_path);
		return (-1);
	}
	return (fd);
}

void	save_stds(t_data *d)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		d->saved_stds[i] = dup(i);
		if (d->saved_stds[i] == -1)
			custom_exit(d, "Failed to save original fd", NULL, EXIT_FAILURE);
	}
}

void	reset_redir(t_data *d)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (d->saved_stds[i] != -1)
		{
			if (dup2(d->saved_stds[i], i) == -1)
				custom_exit(d, "Failed to restore std", NULL, EXIT_FAILURE);
			close(d->saved_stds[i]);
			d->saved_stds[i] = -1;
		}
	}
}

void	restore_fds(t_data *d)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (d->base_stds[i] != -1)
		{
			if (dup2(d->base_stds[i], i) == -1)
				custom_exit(d, "Failed to restore std\n", NULL, EXIT_FAILURE);
			close(d->base_stds[i]);
			d->base_stds[i] = -1;
		}
	}
}
