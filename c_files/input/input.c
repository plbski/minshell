/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:51:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/16 22:30:32 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	*pre_compute_lens(int amount, const char **cols)
{
	int	*lens;
	int	i;

	lens = malloc(sizeof(int) * (amount + 1));
	i = -1;
	while (++i < amount)
		lens[i] = ft_strlen(cols[i]);
	return (lens);
}

static void	play_anim(char *str, int i, int bt, int time)
{
	const char	*cols[] = {DR15, DR14, DR13, DR12, DR11, DR10, DR9, \
		DR8, DR7, DR6, DR5, DR4, DR3, DR2, DR1};
	const char	*color;
	int			*lens;
	int			index;

	lens = pre_compute_lens(15, cols);
	time = 10;
	while (1)
	{
		bt = 0;
		if (time++ % 1000 == 0 && !ioctl(STDIN_FILENO, FIONREAD, &bt) && bt > 0)
			break ;
		write(1, "\r", 1);
		i = -1;
		while (str[++i])
		{
			index = ((i / 3) + time / 1500) % 15;
			color = cols[index];
			write(1, color, lens[index]);
			write(1, &str[i], 1);
		}
		write(1, RESET, 5);
	}
}

static void	init_anim(t_data *d, char *prompt)
{
	char		*str;
	char		*shlvl;
	int			i;

	shlvl = ft_itoa(d->shlvl);
	str = ms_strjoin(d, START_ANIM_TEXT, shlvl);
	free(shlvl);
	write(1, "\033[?25l\n", 7);
	write(1, prompt, ft_strlen(prompt));
	write(1, "█", 3);
	write(1, "\033[A", 3);
	set_nonblocking_mode(1);
	play_anim(str, 0, 0, 0);
	set_nonblocking_mode(0);
	write(1, "\r", 1);
	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
	write(1, RESET, 5);
	write(1, "\n\033[?25h", 7);
	free(str);
}

static void	split_seglen(t_data *d, char **str, int prompt_len, char *col)
{
	char	**splits;
	int		i;
	int		seg_len;

	if (!char_in_str('/', *str) || prompt_len <= 0)
		return ;
	splits = ms_split(d, *str, '/');
	seg_len = prompt_len / get_arr_len((void **)splits);
	i = 0;
	while (splits[++i])
	{
		if (i == 1 && splits[i][0] != '~' && !splits[i + 1])
			setstr(d, &splits[i], ms_strjoin(d, "/", splits[i]));
		if (!splits[i + 1] || char_in_str('$', splits[i]))
			setstr(d, &splits[i], ms_strjoin(d, col, splits[i]));
		else
		{
			if (seg_len > 0 && ft_strlen(splits[i]) > seg_len)
				ms_substr(d, &splits[i], 0, seg_len);
			setstr(d, &splits[i], ms_strjoin(d, splits[i], "/"));
		}
	}
	setstr(d, str, contract_str(d, splits));
	free_void_array((void ***)&splits);
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
	split_seglen(d, &prompt_msg, PROMPT_SEGLEN, PROMPT_CWD_END);
	if (!prompt_msg)
		custom_exit(d, "Prompt alloc failed", NULL, EXIT_FAILURE);
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
