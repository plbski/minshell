/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plbuet <plbuet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:51:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/28 19:12:27 by plbuet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	heredoc(char *end, t_data *d, char *print)
{
	char	*line;
	int		pipefd[2];
	int		len;
	int		len_print;

	len_print = ft_strlen(print);
	len = 0;
	end =remove_chars(end, " ");
	if (pipe(pipefd) == -1)
		custom_exit(d, "erreur pipe", NULL, EXIT_FAILURE);
	while(1)
	{
		write(1, print, len_print);
		line = get_next_line(0);
		line == NULL && (custom_exit(d, "erreur gnl", NULL, EXIT_FAILURE));
		line = truncate_at_end(line, '\n');
		len = ft_strlen(line);
		if (ft_strncmp(line, end, len) == 0)
			break;
		write(pipefd[1], line, len);
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	close(pipefd[0]);
}
int	handle_splits(t_data *d, char *prompt)
{
	char	**splits;
	int		i;

	prompt = redir(d, prompt);
	splits = ft_split_str(prompt, "&&");
	if (!splits)
		return (0);
	i = -1;
	while (splits[++i])
		execute_prompt(d, splits[i]);
	free(splits);
	return (1);
}

char	*get_prompt_message(t_data *d)
{
	char	*logname_part;
	char	*cwd_part;
	char	*prompt_msg;
	char	*icon_part;

	logname_part = ft_str_mega_join(PROMPT_LOGNAME_COL, d->logname, " ", RESET);
	if (!logname_part)
		return (NULL);
	icon_part = ft_str_mega_join(MAGENTA, "$ ", RESET, NULL);
	cwd_part = ft_str_mega_join(PROMPT_CWD_COL, d->cwd, icon_part, RESET);
	prompt_msg = ft_strjoin(logname_part, cwd_part);
	free(icon_part);
	free(cwd_part);
	free(logname_part);
	return (prompt_msg);
}

int	is_valid_prompt(char *prompt)
{
	int	i;

	if (!prompt || prompt[0] == '\0')
		return (0);
	i = -1;
	while (prompt[++i])
	{
		if (prompt[i] != ' ')
			return (1);
	}
	return (0);
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
