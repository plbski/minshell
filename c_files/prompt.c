/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:51:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/15 16:06:47 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	show_doc(char *prompt_line)
{
	char	*path_with_txt;
	char	*cmd_name;
	char	*full_path;

	cmd_name = ft_strtrim(prompt_line, "man ");
	if (!cmd_name)
		return (0);
	if (!ft_strncmp(cmd_name, "", 1))
		return (ft_printf("MAN command: man (name_of_argument).\n"), 1);
	path_with_txt = ft_strjoin(cmd_name, ".txt");
	if (!path_with_txt)
		return (0);
	full_path = ft_strjoin("DOC/", path_with_txt);
	if (!full_path)
		return (0);
	if (access(full_path, F_OK) == -1)
		printf("\"%s\" file not found in %s\n", cmd_name, full_path);
	free(full_path);
	free(cmd_name);
	free(path_with_txt);
	return (1);
}

void	execute_prompt(t_data *d, char *prompt)
{
	(void)d;

	if (!ft_strncmp(prompt, "clear", 4))
		system("clear");
	if (!ft_strncmp(prompt, "man", 3))
		show_doc(prompt);
	if (!ft_strncmp(prompt, "pwd", 3))
		pwd(d);
	if (!ft_strncmp(prompt, "cd", 2))
		ft_cd(d, prompt);
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
		terminal_line = readline("Minishell$ ");
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
