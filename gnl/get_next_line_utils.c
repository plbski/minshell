/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:14:54 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/11 08:47:37 by giuliovalen      ###   ########.fr       */
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

int	update_fd(t_data *d, int fd, int index, ssize_t	b_read)
{
	char	buffer[BUFFER_SIZE + 1];
	char	full_buffer[MAXSIZE + 1];
	int		i;
	ssize_t	tot_size;

	tot_size = 0;
	full_buffer[0] = '\0';
	buffer[0] = '\0';
	while (!contains(buffer, '\n') && index < MAXSIZE && b_read == BUFFER_SIZE)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read < 0)
			return (-1);
		if (!b_read)
			break ;
		tot_size += b_read;
		buffer[b_read] = '\0';
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
