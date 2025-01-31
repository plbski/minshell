/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:11:24 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/31 17:51:38 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	handle_heredoc_interrupt(char **full)
{
	if (g_quit_in_heredoc)
	{
		write(1, "\n", 1);
		g_quit_in_heredoc = 0;
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

static char	*exec_heredoc(t_data *d, char *nd, char *print, int is_q)
{
	char	*lin;
	int		print_prompt;
	char	*full;

	print_prompt = 1;
	full = ms_strdup(d, "\n");
	while (1)
	{
		lin = readline(print);
		if (!lin)
			break ;
		if (handle_heredoc_interrupt(&full))
			break ;
		if (should_skip_line(lin, &print_prompt))
			continue ;
		if (!nd || cmp_str(lin, nd) || (is_q && chr_amnt(lin, *nd) % 2 == 1))
			break ;
		full = ms_strjoin(d, full, lin);
		safe_free(lin);
	}
	if (is_q && full)
		full = ms_strjoin(d, full, lin);
	return (safe_free(lin), full);
}

char	*heredoc(char *end, t_data *d, char *print, int is_quote)
{
	char	*heredoc_return;

	setup_signal(1, 1);
	heredoc_return = exec_heredoc(d, end, print, is_quote);
	g_quit_in_heredoc = 0;
	setup_signal(0, 0);
	return (heredoc_return);
}
