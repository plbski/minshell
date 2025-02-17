/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 03:26:34 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/16 22:42:28 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

static int	add_character(char *str, int i, int *sgqt, int *dbqt)
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

int	is_only_quotes(char *str)
{
	int	i;
	int	only_qt;

	only_qt = 1;
	i = -1;
	while (str[++i])
		if (str[i] != '\'' && str[i] != '\"')
			only_qt = 0;
	return (only_qt);
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
	if (is_only_quotes(*str))
	{
		free(*str);
		*str = NULL;
		return ;
	}
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

int	is_in_quote(char *str, int index)
{
	int	i;
	int	in_double_quote;
	int	in_single_quote;

	in_double_quote = 0;
	in_single_quote = 0;
	i = -1;
	while (str[++i] && i <= index)
	{
		if (str[i] == '\"' && !in_single_quote && i < index)
			in_double_quote = !in_double_quote;
		else if (str[i] == '\'' && !in_double_quote && i < index)
			in_single_quote = !in_single_quote;
	}
	if (in_double_quote)
		return (2);
	else if (in_single_quote)
		return (1);
	return (0);
}

char	*get_last_line(t_data *d, const char *filename)
{
	int		fd;
	char	*line;
	char	*last_line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	last_line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		safe_free(last_line);
		last_line = ms_strdup(d, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (last_line);
}
