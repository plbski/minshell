/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:51:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/28 15:28:58 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	handle_splits(t_data *d, char *prompt)
{
	char	**splits;
	int		i;

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
