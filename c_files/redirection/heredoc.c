/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:11:24 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/25 19:27:23 by gvalente         ###   ########.fr       */
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
	return (setup_signal(0, 0), 1);
}

char	*ft_heredoc(char *end, t_data *d, char *print)
{
	int		heredoc_fd;
	int		heredoc_success;
	char	*file_name;

	file_name = NULL;
	setstr(d, &file_name, name_heredoc(d));
	if (!file_name)
		custom_exit(d, "name in heredoc", NULL, EXIT_FAILURE);
	heredoc_fd = open(file_name, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (heredoc_fd == -1)
	{
		safe_free(file_name);
		custom_exit(d, "error in heredoc", NULL, EXIT_FAILURE);
	}
	setup_signal(1, 1);
	heredoc_success = exec_heredoc(end, print, heredoc_fd);
	close(heredoc_fd);
	if (heredoc_success)
		return (file_name);
	ft_dprintf(2, "msh: write error: Broken pipe\n");
	safe_free(file_name);
	return (NULL);
}
