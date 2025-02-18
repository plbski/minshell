/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:51:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/18 02:05:50 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static void	play_anim(char *str, int i, int bt, const char **cols)
{
	int			time;
	int			lens[14];
	int			index;

	time = -1;
	while (++time < 14)
		lens[time] = ft_strlen(cols[time]);
	while (time++ < 50000)
	{
		bt = 0;
		if (!ioctl(STDIN_FILENO, FIONREAD, &bt) && bt > 0)
			break ;
		write(1, "\r", 1);
		i = -1;
		while (str[++i])
		{
			index = ((i / 3) + time / 500) % 14;
			write(1, cols[index], lens[index]);
			write(1, &str[i], 1);
		}
		write(1, RESET, 5);
	}
}

static void	init_anim(t_data *d, char *prompt)
{
	const char	*cols[] = {DR15, DR14, DR13, DR12, DR11, DR10, DR9, \
		DR8, DR7, DB0, DB1, DB2, DB3, DB4, DB4};
	char		*str;
	char		*shlvl;

	shlvl = ft_itoa(d->shlvl);
	str = ms_strjoin(d, START_ANIM_TEXT, shlvl);
	free(shlvl);
	write(1, "\033[?25l\n", 7);
	write(1, prompt, ft_strlen(prompt));
	write(1, "█\033[A", 6);
	setup_signal(1, 0);
	set_nonblocking_mode(1, &d->oldt);
	play_anim(str, 0, 0, cols);
	set_nonblocking_mode(0, &d->oldt);
	setup_signal(0, 0);
	write(1, "\r", 1);
	write(1, RESET, 5);
	write(1, "\n\033[?25h", 7);
	write(1, "\033[K", 3);
	free(str);
}

static void	split_seglen(t_data *d, char **str, char *headcol)
{
	const char	*cl[] = {D4, D3, D2, D1, D0};
	char		**splits;
	int			i;
	int			arr_len;
	int			seg_len;

	splits = ms_split(d, *str, '/');
	arr_len = get_arr_len((void **)splits);
	i = arr_len;
	while (i-- > 1)
	{
		if (i == 1 && splits[i][0] != '~' && !splits[i + 1])
			setstr(d, &splits[i], ms_strjoin(d, "/", splits[i]));
		if (!splits[i + 1] || char_in_str('$', splits[i]))
			setstr(d, &splits[i], ms_strjoin(d, headcol, splits[i]));
		else
			setstr(d, &splits[i], ft_megajoin(cl[(i * 5) / arr_len], \
				splits[i], "/", DRESET));
	}
	setstr(d, str, contract_str(d, splits));
	free_void_array((void ***)&splits);
}

char	*get_prompt_message(t_data *d)
{
	char	*msh;
	char	*cwd_part;
	char	*cut_cwd;
	char	*prompt_msg;

	msh = ft_megajoin("\001" PRM_START "\002", "msh ", DRESET, NULL);
	if (!msh)
		return (NULL);
	cut_cwd = ms_strdup(d, d->cwd);
	replace_strstr(d, &cut_cwd, d->home_wd, "~");
	setstr(d, &cut_cwd, ms_strjoin(d, "/", cut_cwd));
	cwd_part = ms_strjoin(d, "", cut_cwd);
	free(cut_cwd);
	if (!cwd_part)
		custom_exit(d, "alloc of cwd_part (prompt)\n", NULL, EXIT_FAILURE);
	prompt_msg = ms_strjoin(d, msh, cwd_part);
	if (char_in_str('/', prompt_msg) && PRM_SEGLEN > 0)
		split_seglen(d, &prompt_msg, "\001" PRM_HEAD "\002");
	if (!prompt_msg)
		custom_exit(d, "Prompt alloc failed", NULL, EXIT_FAILURE);
	setstr(d, &prompt_msg, \
			ft_megajoin(prompt_msg, "\001" PRM_CMB "\002", "$ ", DRESET));
	return (free(cwd_part), free(msh), prompt_msg);
}

int	process_input(t_data *d, int start)
{
	char	*prompt;
	char	*user_input;

	prompt = get_prompt_message(d);
	if (start)
		init_anim(d, prompt);
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
		exec_input(d, user_input);
		safe_free(d->prv_input);
		d->prv_input = ms_strdup(d, user_input);
		update_env_variables(d);
	}
	return (free(user_input), rl_replace_line("", 0), rl_on_new_line(), 1);
}
