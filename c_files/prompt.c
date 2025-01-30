/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:51:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/30 13:58:04 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

#include <errno.h>

int	is_stdin_closed(void)
{
	char		buffer[1];
	ssize_t		result;

	result = read(STDIN_FILENO, buffer, 1);
	return (result == -1 && errno == EBADF);
}

char	*heredoc(char *end, t_data *d, char *print, int is_quote)
{
	char	*input;
	char	*line;
	int		pipefd[2];

	input = ft_strdup("");
	end = remove_chars(end, " ");
	if (pipe(pipefd) == -1)
		custom_exit(d, "erreur pipe", NULL, EXIT_FAILURE);
	setup_signal(1, 1);
	while (1)
	{
		line = readline(print);
		if (is_stdin_closed())
		{
			break ;
		}
		line = truncate_at_end(line, '\n');
		if (is_same_string(line, end))
			break ;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		input = ft_strjoin(input, line);
		free(line);
		if (is_quote && ch_amount(input, end[0]) % 2 == 1)
			break ;
	}
	setup_signal(0, 0);
	return (close(pipefd[1]), close(pipefd[0]), free(end), input);
}

int	handle_splits(t_data *d, char *prompt)
{
	char	**splits;
	int		i;

	if (ch_amount(prompt, '<') || ch_amount(prompt, '>'))
	{
		execute_redir(d, prompt);
		if (!prompt[0])
			return (1);
	}
	splits = ft_split_str(prompt, "&&");
	if (!splits)
		return (0);
	i = -1;
	while (splits[++i])
		execute_prompt(d, splits[i]);
	free(splits);
	return (1);
}

int	get_terminal_prompt(t_data *d)
{
	char	*prompt_msg;
	char	*terminal_line;

	if (!d->cwd)
		custom_exit(d, "No cwd", NULL, EXIT_FAILURE);
	prompt_msg = get_prompt_message(d);
	if (!prompt_msg)
		custom_exit(d, "Prompt alloc failed", NULL, EXIT_FAILURE);
	terminal_line = readline(prompt_msg);
	if (!terminal_line)
		return (0);
	get_quote_termination(d, &terminal_line);
	if (is_valid_prompt(terminal_line))
	{
		add_history(terminal_line);
		handle_splits(d, terminal_line);
	}
	free(terminal_line);
	free(prompt_msg);
	return (1);
}
