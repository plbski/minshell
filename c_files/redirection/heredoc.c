/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:11:24 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/21 19:36:28 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static int	handle_interruptions(char *line)
{
	if (g_quit_in_heredoc)
	{
		write(1, "\n", 1);
		g_quit_in_heredoc = 0;
		safe_free(line);
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

int	exec_heredoc(char *nd, char *print, int heredoc_fd)
{
	char	*line;
	int		print_prompt;

	print_prompt = 1;
	while (1)
	{
		if (print_prompt)
			ft_dprintf(STDOUT_FILENO, "%s", print);
		print_prompt = 1;
		line = get_next_line(STDIN_FILENO);
		if (handle_interruptions(line))
			return (0);
		if (should_skip_line(line, &print_prompt))
			continue ;
		line[ft_strlen(line) - 1] = '\0';
		if (!nd || same_str(line, nd))
		{
			free(line);
			break ;
		}
		write(heredoc_fd, line, ft_strlen(line));
		write(heredoc_fd, "\n", 1);
		safe_free(line);
	}
	return (1);
}

int	ft_heredoc(char *end, t_data *d, char *print)
{
	int	heredoc_fd;
	int	heredoc_success;

	heredoc_fd = open(d->heredoc_wd, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (heredoc_fd == -1)
		custom_exit(d, "error in heredoc", NULL, EXIT_FAILURE);
	setup_signal(1, 1);
	heredoc_success = exec_heredoc(end, print, heredoc_fd);
	setup_signal(0, 0);
	if (!heredoc_success)
	{
		close(heredoc_fd);
		printf("msh: write error: Broken pipe\n");
		return (-1);
	}
	return (heredoc_fd);
}
