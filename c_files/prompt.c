/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:51:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/24 14:08:17 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

/**
 * @note 
 * @attention 
 * @todo 
 */
int	handle_splits(t_data *d, char *prompt)
{
	char	**splits;
	int		i;

	(void)d;
	splits = ft_split_str(prompt, "&&");
	if (!splits)
		return (0);
	i = -1;
	while (splits[++i])
		execute_prompt(d, splits[i]);
	return (1);
}

void	execute_prompt(t_data *d, char *prompt)
{
	char	**splits;
	char	*arg;
	char	*flag;
	int		i;

	arg = NULL;
	flag = NULL;
	splits = ft_split(prompt, ' ');
	if (splits)
	{
		arg = splits[1];
		if (arg)
			flag = splits[2];
	}
	i = -1;
	while (d->bltin_names[++i])
		if (!ft_strncmp(prompt, d->bltin_names[i], ft_strlen(d->bltin_names[i])))
			d->builtin_funcs[i](d, arg, flag, 1);
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
			custom_exit(d, NULL, NULL, 0);
		add_history(terminal_line);
		handle_splits(d, terminal_line);
		free(terminal_line);
		free(prompt_msg);
	}
	else
		perror("getcwd");
	return (1);
}
