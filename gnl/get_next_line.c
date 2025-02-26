/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:14:54 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/14 21:18:25 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	contains(const char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (1);
	return (0);
}

char	*ft_strdup(const char *s)
{
	char	*res;
	int		size;
	int		i;

	size = 0;
	while (s[size])
		size++;
	res = malloc(size + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (s[++i])
		res[i] = s[i];
	res[i] = '\0';
	return (res);
}

void	upd_buffers(t_data *d, char buffer[])
{
	int	i;
	int	buffer_index;
	int	lftover_index;

	buffer_index = 0;
	lftover_index = 0;
	i = 0;
	while (d->leftover[lftover_index])
	{
		d->buffer[buffer_index++] = d->leftover[lftover_index];
		d->leftover[lftover_index++] = '\0';
	}
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		d->buffer[buffer_index++] = buffer[i++];
	if (buffer[i] == '\n')
		d->buffer[buffer_index++] = buffer[i++];
	d->buffer[buffer_index] = '\0';
	lftover_index = 0;
	while (buffer[i])
		d->leftover[lftover_index++] = buffer[i++];
	d->leftover[lftover_index] = '\0';
}

int	update_fd(t_data *d, int fd, int index, int i)
{
	char	buffer[BUFFER_SIZE + 1];
	char	full_buffer[MAXSIZE + 1];
	ssize_t	bites_read;
	ssize_t	tot_size;

	tot_size = 0;
	full_buffer[0] = '\0';
	buffer[0] = '\0';
	while (!contains(buffer, '\n') && index < MAXSIZE)
	{
		bites_read = read(fd, buffer, BUFFER_SIZE);
		if (bites_read < 0)
			return (-1);
		if (bites_read == 0)
			break ;
		tot_size += bites_read;
		buffer[bites_read] = '\0';
		i = 0;
		while (buffer[i] && index < MAXSIZE)
			full_buffer[index++] = buffer[i++];
	}
	full_buffer[index] = '\0';
	if (tot_size != 0)
		upd_buffers(d, full_buffer);
	return ((int)tot_size);
}

char	*handle_leftover(t_data *d)
{
	char	*s;
	int		i;
	int		j;
	int		new_start;

	new_start = 0;
	while (d->leftover[new_start] && d->leftover[new_start] != '\n')
		new_start++;
	if (d->leftover[new_start] == '\n')
		new_start++;
	s = malloc(new_start + 1);
	if (!s)
		return (NULL);
	i = 0;
	while (i < new_start)
	{
		s[i] = d->leftover[i];
		d->leftover[i++] = '\0';
	}
	s[i] = '\0';
	j = 0;
	while (d->leftover[new_start])
		d->leftover[j++] = d->leftover[new_start++];
	d->leftover[j] = '\0';
	return (s);
}

char	*get_next_line(int fd)
{
	static t_data	t_datas[1024];
	int				status;
	t_data			*d;
	char			*ret;

	if (fd < 0)
		return (NULL);
	d = &t_datas[fd];
	if (contains(d->leftover, '\n'))
		return (handle_leftover(d));
	status = update_fd(d, fd, 0, 0);
	if (status <= 0)
	{
		ret = NULL;
		if (status == -1)
			while (d->leftover[++status])
				d->leftover[status] = '\0';
		if (d->leftover[0])
			ret = ft_strdup(d->leftover);
		d->leftover[0] = '\0';
		return (ret);
	}
	return (ft_strdup(d->buffer));
}
