/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:28:20 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/14 03:51:20 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	handle_interruptions(char **full, char **line)
{
	*line = get_next_line(STDIN_FILENO);
	if (!*line || g_quit_in_heredoc)
	{
		safe_free(*full);
		*full = NULL;
		return (1);
	}
	return (0);
}

static int	should_skip_line(char *line, int *print_line)
{
	if (!line)
	{
		*print_line = 0;
		return (1);
	}
	if (line[0] == '\n')
	{
		free(line);
		return (1);
	}
	*print_line = 1;
	return (0);
}

static void	add_line(t_data *d, char **buffer, char **full, char **line)
{
	*buffer = ms_strjoin(d, *full, *line);
	free(*full);
	*full = *buffer;
	safe_free(*line);
}

static char	*exec_parse_heredoc(t_data *d, char *nd, char *print)
{
	char	*line;
	int		print_prompt;
	char	*full;
	char	*buffer;

	line = NULL;
	print_prompt = 1;
	full = ms_strdup(d, "\n");
	while (1)
	{
		if (print_prompt)
			ft_dprintf(STDOUT_FILENO, "%s", print);
		print_prompt = 1;
		if (handle_interruptions(&full, &line))
			break ;
		if (should_skip_line(line, &print_prompt))
			continue ;
		if (!nd || cmp_str(line, nd) || (chr_amnt(line, *nd) % 2 == 1))
			break ;
		add_line(d, &buffer, &full, &line);
	}
	if (full)
		add_line(d, &buffer, &full, &line);
	return (full);
}

char	*parse_heredoc(char *end, t_data *d, char *print)
{
	char	*heredoc_return;

	setup_signal(1, 1);
	heredoc_return = exec_parse_heredoc(d, end, print);
	setup_signal(0, 0);
	if (!heredoc_return)
	{
		printf("msh: unexpected EOF while looking for matching `%s'\n", end);
		printf("msh: syntax error: unexpected end of file\n");
	}
	g_quit_in_heredoc = 0;
	return (heredoc_return);
}
