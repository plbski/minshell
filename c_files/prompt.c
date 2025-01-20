/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:51:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/15 00:14:36 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	execute_prompt(t_data *d, char *prompt)
{
	if (!ft_strncmp(prompt, "clear", 4))
		system("clear");
	if (!ft_strncmp(prompt, "man", 3))
		man(d, prompt);
	if (!ft_strncmp(prompt, "ls", 2))
		ls(d);
	if (!ft_strncmp(prompt, "cd", 2))
		cd(d, prompt);
	if (!ft_strncmp(prompt, "pwd", 3))
		pwd(d);
}

int	get_terminal_prompt(t_data *d)
{
	char	*terminal_line;
	char	*prompt_msg;

	if (d->cwd)
	{
		prompt_msg = ft_strjoin(d->cwd, PROMPT_ICON);
		if (!prompt_msg)
			return (d->status = closing, 0);
		terminal_line = readline(prompt_msg);
		if (!terminal_line)
			return (d->status = closing, 0);
		add_history(terminal_line);
		execute_prompt(d, terminal_line);
		free(terminal_line);
		free(prompt_msg);
	}
	else
		perror("getcwd");
	return (1);
}
