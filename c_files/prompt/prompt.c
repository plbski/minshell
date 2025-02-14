/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:51:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/13 23:03:27 by giuliovalen      ###   ########.fr       */
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

char	*solo_pipe(t_data *d, char *trm_line)
{
	char	*pipe_ptr;
	char	*add_line;
	char	*tmp;

	pipe_ptr = ft_strrchr(trm_line, '|');
	if (!pipe_ptr)
		return (trm_line);
	while ((*pipe_ptr && *pipe_ptr == ' ') || *pipe_ptr == '|')
		pipe_ptr++;
	if (*pipe_ptr == '\0' || *pipe_ptr == '|')
	{
		printf("%c\n", *pipe_ptr);
		add_line = readline(">");
		if (add_line)
		{
			tmp = trm_line;
			trm_line = ft_str_mega_join(trm_line, " ", add_line, NULL);
			if (!trm_line)
				custom_exit(d, "alloc in solo pipe", NULL, EXIT_FAILURE);
			free(tmp);
			free(add_line);
		}
	}
	return (trm_line);
}

int	get_terminal_prompt(t_data *d)
{
	char	*prompt_msg;
	char	*user_input;

	if (!d->cwd)
		custom_exit(d, "No cwd", NULL, EXIT_FAILURE);
	prompt_msg = get_prompt_message(d);
	if (!prompt_msg)
		custom_exit(d, "Prompt alloc failed", NULL, EXIT_FAILURE);
	user_input = readline(prompt_msg);
	free(prompt_msg);
	if (!user_input)
		return (0);
	if (only_space(user_input))
		return (free(user_input), rl_replace_line("", 0), rl_on_new_line(), 1);
	if (!d->prv_input || !cmp_str(d->prv_input, user_input))
		add_history(user_input);
	if (validate_prmpt(d, &user_input))
	{
		user_input = solo_pipe(d, user_input);
		exec_prompt(d, user_input);
		safe_free(d->prv_input);
		d->prv_input = ms_strdup(d, user_input);
		update_env_variables(d);
	}
	return (free(user_input), rl_replace_line("", 0), rl_on_new_line(), 1);
}
