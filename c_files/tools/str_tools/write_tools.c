/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:06:54 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/03/04 10:58:02 by giuliovalen      ###   ########.fr       */
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

int	get_char_index(const char *str, char c)
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
	char	*line;
	char	*buffer;

	full_content = ms_strdup(d, "");
	line = get_next_line(fd);
	while (line)
	{
		buffer = ms_strjoin(d, full_content, line);
		free(line);
		free(full_content);
		full_content = buffer;
		line = get_next_line(fd);
	}
	return (full_content);
}
