/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:51:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/16 13:53:54 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static void	split_seglen(t_data *d, char **str, int prompt_len, char *col)
{
	char	**splits;
	int		i;
	int		seg_len;

	if (!char_in_str('/', *str) || prompt_len <= 0)
		return ;
	splits = ms_split(d, *str, '/');
	seg_len = prompt_len / get_arr_len((void **)splits);
	if (seg_len <= 0)
		seg_len = 1;
	i = 0;
	while (splits[++i])
	{
		if (i == 1 && splits[i][0] != '~' && !splits[i + 1])
			setstr(d, &splits[i], ms_strjoin(d, "/", splits[i]));
		if (!splits[i + 1] || char_in_str('$', splits[i]))
			setstr(d, &splits[i], ms_strjoin(d, col, splits[i]));
		else
		{
			if (ft_strlen(splits[i]) > seg_len)
				ms_substr(d, &splits[i], 0, seg_len);
			setstr(d, &splits[i], ms_strjoin(d, splits[i], "/"));
		}
	}
	setstr(d, str, contract_str(d, splits));
}

static char	*get_prompt_message(t_data *d)
{
	char	*msh;
	char	*cwd_part;
	char	*cut_cwd;
	char	*prompt_msg;
	char	*icon_part;

	msh = ft_str_mega_join(PROMPT_LOGNAME_COL, "msh ", "\033[1;35m❯ ", RESET);
	if (!msh)
		return (NULL);
	cut_cwd = ms_strdup(d, d->cwd);
	replace_strstr(d, &cut_cwd, d->home_wd, "~");
	setstr(d, &cut_cwd, ms_strjoin(d, "/", cut_cwd));
	icon_part = ft_str_mega_join(MAGENTA, "$ ", RESET, NULL);
	if (!icon_part)
		custom_exit(d, "alloc of icon_part (prompt)\n", NULL, EXIT_FAILURE);
	cwd_part = ft_str_mega_join(PROMPT_CWD_COL, cut_cwd, icon_part, RESET);
	free(cut_cwd);
	free(icon_part);
	if (!cwd_part)
		custom_exit(d, "alloc of cwd_part (prompt)\n", NULL, EXIT_FAILURE);
	prompt_msg = ms_strjoin(d, msh, cwd_part);
	free(cwd_part);
	free(msh);
	split_seglen(d, &prompt_msg, PROMPT_SEGLEN, PROMPT_CWD_END);
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

int	process_input(t_data *d)
{
	char	*prompt;
	char	*user_input;

	if (!d->cwd)
		custom_exit(d, "No cwd", NULL, EXIT_FAILURE);
	prompt = get_prompt_message(d);
	if (!prompt)
		custom_exit(d, "Prompt alloc failed", NULL, EXIT_FAILURE);
	user_input = readline(prompt);
	free(prompt);
	if (!user_input)
		return (0);
	if (only_space(user_input))
		return (free(user_input), rl_replace_line("", 0), rl_on_new_line(), 1);
	if (!d->prv_input || !same_str(d->prv_input, user_input))
		add_history(user_input);
	if (validate_input(d, &user_input))
	{
		user_input = solo_pipe(d, user_input);
		exec_input(d, user_input);
		safe_free(d->prv_input);
		d->prv_input = ms_strdup(d, user_input);
		update_env_variables(d);
	}
	return (free(user_input), rl_replace_line("", 0), rl_on_new_line(), 1);
}
