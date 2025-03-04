/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:51:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/03/04 12:09:16 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static void	play_anim(const char *str, int i, int bt, const char **cols)
{
	int			time;
	int			lens[14];
	int			index;

	time = -1;
	while (++time < 14)
		lens[time] = ft_strlen(cols[time]);
	while (time++ < 44000)
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

int	process_input(t_data *d, int start)
{
	char	*user_input;

	if (!d->prompt_msg)
		d->prompt_msg = get_prompt_message(d);
	if (!d->prompt_msg)
		d->prompt_msg = ms_strdup(d, "Minishell > ");
	if (start && d->fork_child == 0)
		init_anim(d, d->prompt_msg);
	user_input = readline(d->prompt_msg);
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
