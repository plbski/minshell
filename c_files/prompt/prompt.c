/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plbuet <plbuet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:51:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/09 18:51:25 by plbuet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static char	*get_prompt_message(t_data *d)
{
	char	*logname_part;
	char	*cwd_part;
	char	*cut_cwd;
	char	*prompt_msg;
	char	*icon_part;

	logname_part = ft_str_mega_join(PROMPT_LOGNAME_COL, d->logname, " ", RESET);
	if (!logname_part)
		return (NULL);
	cut_cwd = replace_str(d, d->cwd, d->home_wd, "~");
	icon_part = ft_str_mega_join(MAGENTA, "$ ", RESET, NULL);
	cwd_part = ft_str_mega_join(PROMPT_CWD_COL, cut_cwd, icon_part, RESET);
	free(cut_cwd);
	prompt_msg = ms_strjoin(d, logname_part, cwd_part);
	free(icon_part);
	free(cwd_part);
	free(logname_part);
	return (prompt_msg);
}
char *solo_pipe(char *terminale_line)
{
	char	*pipe_ptr;
	char	*additional_line;
	char	*tmp;

	pipe_ptr = ft_strrchr(terminale_line, '|');
	if (!pipe_ptr)
		return (terminale_line);
	while ((*pipe_ptr && *pipe_ptr == ' ') || *pipe_ptr == '|')
		pipe_ptr++;
	if (*pipe_ptr == '\0' || *pipe_ptr == '|')
	{
		printf("%c\n", *pipe_ptr);
		additional_line = readline(">");
		if (additional_line)
		{
			tmp = terminale_line;
			terminale_line = ft_str_mega_join(terminale_line, " ", additional_line, NULL);
			free(tmp);
			free(additional_line);
		}
	}
	printf("terminal : %s\n", terminale_line);
	return (terminale_line);
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
	free(prompt_msg);
	if (!terminal_line)
		return (0);
	terminal_line = solo_pipe(terminal_line);
	if (validate_prmpt(d, &terminal_line))
	{
		add_history(terminal_line);
		exec_prompt(d, terminal_line);
		update_env_variables(d);
	}
	free(terminal_line);
	rl_replace_line("", 0);
	rl_on_new_line ();
	return (1);
}
