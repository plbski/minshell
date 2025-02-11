/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:06:54 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/11 18:17:24 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	*replace_str(t_data *d, char *str, char *remove, char *replace)
{
	char	*new_str;
	int		i;
	int		j;
	char	*joined;

	if (!str || !remove)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		j = 0;
		while (remove[j] && remove[j] == str[i + j])
			j++;
		if (remove[j])
			continue ;
		new_str = ms_strdup(d, str + i + j);
		joined = ms_strjoin(d, replace, new_str);
		free(new_str);
		return (joined);
	}
	return (ms_strdup(d, str));
}

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

void	reverse_str_array(char **arr, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = size - 1;
	while (i < j)
	{
		temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
		i++;
		j--;
	}
}
