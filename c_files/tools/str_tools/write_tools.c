/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:06:54 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/14 04:23:13 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

char	*read_file(t_data *d, int fd)
{
	char	*line;
	char	*buffer;
	char	*content;

	line = get_next_line(fd);
	content = ms_strdup(d, "");
	while (line != NULL)
	{
		buffer = ms_strjoin(d, content, line);
		free(content);
		content = buffer;
		free(line);
		line = get_next_line(fd);
	}
	return (content);
}

int	is_builtin_cmd(t_data *d, char *str)
{
	int	i;

	i = -1;
	while (d->bltin_names[++i])
		if (cmp_str(str, d->bltin_names[i]))
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
	char	*line;
	char	*full;
	char	*tmp;

	full = ms_strdup(d, "");
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strjoin(full, line);
		free(full);
		full = tmp;
		free(line);
		line = get_next_line(fd);
	}
	return (full);
}