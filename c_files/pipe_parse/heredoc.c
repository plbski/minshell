/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:11:24 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/10 15:16:47 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	handle_heredoc_interrupt(void)
{
	if (g_quit_in_heredoc)
	{
		write(1, "\n", 1);
		g_quit_in_heredoc = 0;
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

static void	exec_heredoc(t_data *d, char *nd, char *print)
{
	char	*line;
	int		print_prompt;

	while (1)
	{
		ft_dprintf(STDOUT_FILENO, "%s", print);
		line = get_next_line(STDIN_FILENO);
		if (!line || handle_heredoc_interrupt())
			break ;
		if (should_skip_line(line, &print_prompt))
			continue ;
		line[ft_strlen(line) - 1] = '\0';
		if (!nd || cmp_str(line, nd))
		{
			free(line);
			break ;
		}
		ft_dprintf(d->heredocpipe[1], "%s\n", line);
		safe_free(line);
	}
	close(d->heredocpipe[1]);
}

void	ft_heredoc(char *end, t_data *d, char *print)
{
	if (pipe(d->heredocpipe) == -1)
		custom_exit(d, "pipe error", NULL, EXIT_FAILURE);
	save_original_fds(d);
	setup_signal(1, 1);
	exec_heredoc(d, end, print);
	g_quit_in_heredoc = 0;
	setup_signal(0, 0);
	if (dup2(d->heredocpipe[0], STDIN_FILENO) == -1)
		custom_exit(d, "erreur dup2 dans heredoc", NULL, EXIT_FAILURE);
	close(d->heredocpipe[0]);
}
