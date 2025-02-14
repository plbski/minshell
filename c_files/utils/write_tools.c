/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:06:54 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/14 01:53:30 by giuliovalen      ###   ########.fr       */
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

char	*char_join(char a, char b, char c, char d)
{
	const char	chars[] = {a, b, c, d};
	char		*str;
	int			len;
	int			i;

	len = 0;
	i = -1;
	while (++i < 4)
		if (chars[i])
			len++;
	if (!len)
		return (NULL);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	len = 0;
	i = -1;
	while (++i < 4)
		if (chars[i])
			str[len++] = chars[i];
	str[len] = '\0';
	return (str);
}

int	add_character(char *str, int i, int *sgqt, int *dbqt)
{
	if (str[i] == '\'' && !(*dbqt))
		return (*sgqt = !(*sgqt), 0);
	if (str[i] == '\"' && !(*sgqt))
		return (*dbqt = !(*dbqt), 0);
	if (!(*sgqt) && !(*dbqt))
		return (str[i] != '\'' && str[i] != '\"');
	else
		return (1);
}

void	remove_quotes(t_data *d, char **str)
{
	char	*new_str;
	int		i;
	int		j;
	int		sgqt;
	int		dbqt;

	if (!str || !*str)
		return ;
	sgqt = 0;
	dbqt = 0;
	i = -1;
	j = 0;
	new_str = ms_malloc(d, ft_strlen(*str) + 1);
	while ((*str)[++i])
		if (add_character(*str, i, &sgqt, &dbqt))
			new_str[j++] = (*str)[i];
	new_str[j] = '\0';
	free(*str);
	*str = new_str;
}
