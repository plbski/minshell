/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:11:24 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/31 09:01:02 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	handle_heredoc_interrupt(void)
{
	if (g_quit_in_heredoc)
	{
		write(1, "\n", 1);
		g_quit_in_heredoc = 0;
		return (1);
	}
	return (0);
}

int	should_skip_line(char *line, int *print_line)
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
	return (0);
}

char	*get_pipe(int fd)
{
	char	buffer[1024];
	char	*result = NULL;
	char	*temp;
	ssize_t	bytes_read;
	size_t	total_size = 0;

	while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		temp = malloc(total_size + bytes_read + 1);
		if (!temp)
		{
			free(result);
			return (NULL);
		}
		if (result)
		{
			ft_memcpy(temp, result, total_size);
			free(result);
		}
		ft_memcpy(temp + total_size, buffer, bytes_read + 1);
		result = temp;
		total_size += bytes_read;
	}
	return (result);
}

void	exec_heredoc(char *end, char *print, int is_quote, int pipefd[2])
{
	char	*line;
	int		print_prompt;

	print_prompt = 1;
	line = NULL;
	setup_signal(1, 1);
	while (1)
	{
		line = readline(print);
		print_prompt = 1;
		if (handle_heredoc_interrupt())
			break ;
		if (should_skip_line(line, &print_prompt))
			continue ;
		if (is_same_string(line, end))
			break ;
		write(pipefd[1], line, ft_strlen(line));
		if (is_quote && ch_amount(line, end[0]) % 2 == 1)
			break ;
		free(line);
	}
	if (line)
		free(line);
	setup_signal(0, 0);
}

char	*heredoc(char *end, t_data *d, char *print, int is_quote)
{
	int		pipefd[2];
	char	*pipe_content;

	if (pipe(pipefd) == -1)
		custom_exit(d, "error: pipe failed", NULL, EXIT_FAILURE);
	exec_heredoc(end, print, is_quote, pipefd);
	close(pipefd[1]);
	pipe_content = get_pipe(pipefd[0]);
	close(pipefd[0]);
	return (pipe_content);
}
