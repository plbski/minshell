/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:06:54 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/18 11:18:34 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../msh.h"

int	is_builtin_cmd(t_data *d, char *str)
{
	int	i;

	i = -1;
	while (d->bltin_names[++i])
		if (same_str(str, d->bltin_names[i]))
			return (1);
	return (0);
}

int	is_all_digit(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

int	get_char_index(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

char	*get_fd_content(t_data *d, int fd)
{
	char	*full_content;
	char	buffer[99999];
	char	*tmp;
	ssize_t	bytes_read;
	size_t	total_length;

	total_length = 0;
	full_content = ms_strdup(d, "");
	bytes_read = read(fd, buffer, 99999);
	while (bytes_read > 0)
	{
		tmp = ms_realloc(d, full_content, total_length + bytes_read + 1);
		if (!tmp)
			return (free(full_content), NULL);
		full_content = tmp;
		ft_memcpy(full_content + total_length, buffer, bytes_read);
		total_length += bytes_read;
		full_content[total_length] = '\0';
		bytes_read = read(fd, buffer, 99999);
	}
	if (bytes_read == -1)
		return (free(full_content), NULL);
	return (full_content);
}
