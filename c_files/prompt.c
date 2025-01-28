/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:51:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/29 00:24:44 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	heredoc(char *end, t_data *d, char *print)
{
	char	*line;
	int		pipefd[2];
	int		len_print;

	len_print = ft_strlen(print);
	end = remove_chars(end, " ");
	if (pipe(pipefd) == -1)
		custom_exit(d, "erreur pipe", NULL, EXIT_FAILURE);
	while (1)
	{
		write(1, print, len_print);
		line = get_next_line(0);
		line == NULL && (custom_exit(d, NULL, NULL, EXIT_SUCCESS));
		line = truncate_at_end(line, '\n');
		if (is_same_string(line, end))
			break ;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	free(end);
	close(pipefd[1]);
	close(pipefd[0]);
}

int	handle_splits(t_data *d, char *prompt)
{
	char	**splits;
	int		i;

	if (get_char_occurence(prompt, '<') || get_char_occurence(prompt, '>'))
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
	if (is_valid_prompt(terminal_line))
	{
		add_history(terminal_line);
		handle_splits(d, terminal_line);
	}
	free(terminal_line);
	free(prompt_msg);
	return (1);
}
