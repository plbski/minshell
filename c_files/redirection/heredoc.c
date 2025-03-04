/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:11:24 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/03/04 12:23:07 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static int	handle_interruptions(char **line, char **full)
{
	if (g_quit_in_heredoc || !*line)
	{
		write(1, "\n", 1);
		g_quit_in_heredoc = 0;
		safe_free(*full);
		safe_free(*line);
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

static int	add_line(t_data *d, char *nd, char **full, char **line)
{
	char	*buffer;
	char	*trunc;

	trunc = *line;
	if (trunc[ft_strlen(trunc) - 1] == '\n')
		trunc[ft_strlen(trunc) - 1] = '\0';
	if (!nd || same_str(nd, trunc))
	{
		safe_free(*line);
		return (0);
	}
	buffer = ft_megajoin(*full, *line, "\n", NULL);
	if (!buffer)
		custom_exit(d, "alloc in add line\n", NULL, EXIT_FAILURE);
	free(*full);
	free(*line);
	*full = buffer;
	return (1);
}

char	*exec_heredoc(t_data *d, char *nd, char *print)
{
	char	*full;
	char	*line;
	int		print_prompt;

	full = ms_strdup(d, "");
	print_prompt = 1;
	setup_signal(1, 1);
	while (1)
	{
		if (print_prompt)
			ft_dprintf(STDOUT_FILENO, "%s", print);
		print_prompt = 1;
		line = get_next_line(STDIN_FILENO);
		if (handle_interruptions(&line, &full))
			return (NULL);
		if (should_skip_line(line, &print_prompt))
			continue ;
		if (!add_line(d, nd, &full, &line))
			break ;
	}
	setup_signal(0, 0);
	return (full);
}

int	set_heredoc(t_data *d, t_token *tok)
{
	char	*content;
	char	*end;

	end = ms_strdup(d, tok->next->name);
	remove_quotes(d, &end);
	content = exec_heredoc(d, end, "heredoc> ");
	free(end);
	if (!content)
		return (0);
	tok->next->type = tk_arg;
	setstr(d, &tok->next->cnt_hered, ms_strdup(d, content));
	free(content);
	return (1);
}
