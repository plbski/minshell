/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:51:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/22 16:47:38 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

/**
 * @note 
 * @attention 
 * @todo 
 */
void	execute_prompt(t_data *d, char *prompt)
{
	if (!ft_strncmp(prompt, "export ", 7))
		export(d, prompt);
	else if (!ft_strncmp(prompt, "env", 4))
		print_env(d);
	else if (!ft_strncmp(prompt, "clear", 5))
		system("clear");
	else if (!ft_strncmp(prompt, "exit", 5))
		custom_exit(d, 0);
	else if (!ft_strncmp(prompt, "man ", 4))
		man(d, prompt);
	else if (!ft_strncmp(prompt, "ls", 2))
		ls(d);
	else if (!ft_strncmp(prompt, "cd ", 3))
		cd(d, prompt);
	else if (!ft_strncmp(prompt, "pwd", 4))
		pwd(d);
	else if (!ft_strncmp(prompt, "echo ", 5))
		create_file(d, "hello", "/coucou.txt");
}

char	*get_prompt_message(t_data *d)
{
	char	*logname_part;
	char	*cwd_part;
	char	*prompt_msg;
	char	*icon_part;

	logname_part = ft_strjoin(d->logname, " ");
	if (!logname_part)
		return (NULL);
	set_string_color(&logname_part, PROMPT_LOGNAME_COL);
	icon_part = ft_str_mega_join(MAGENTA, "$ ", RESET, NULL);
	cwd_part = ft_strjoin(d->cwd, icon_part);
	free(icon_part);
	if (!cwd_part)
		return (NULL);
	set_string_color(&cwd_part, PROMPT_CWD_COL);
	prompt_msg = ft_strjoin(logname_part, cwd_part);
	free(logname_part);
	free(cwd_part);
	return (prompt_msg);
}

int	get_terminal_prompt(t_data *d)
{
	char	*prompt_msg;
	char	*terminal_line;

	if (d->cwd)
	{
		prompt_msg = get_prompt_message(d);
		terminal_line = readline(prompt_msg);
		if (!terminal_line)
			return (d->status = quitting, 0);
		add_history(terminal_line);
		execute_prompt(d, terminal_line);
		free(terminal_line);
		free(prompt_msg);
	}
	else
		perror("getcwd");
	return (1);
}
