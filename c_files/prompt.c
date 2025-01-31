/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:51:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/31 00:10:37 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	handle_splits(t_data *d, char *prompt)
{
	char	**splits;
	int		i;

	// if (ch_amount(prompt, '<') || ch_amount(prompt, '>'))
	// {
	// 	handle_redir(d, prompt);
	// 	if (!prompt[0])
	// 		return (1);
	// }
	splits = ft_split_str(prompt, "&&");
	if (!splits)
		return (0);
	i = -1;
	while (splits[++i])
		execute_prompt(d, splits[i]);
	free(splits);
	return (1);
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
	if (!terminal_line)
		return (0);
	if (is_valid_prompt(d, &terminal_line))
	{
		add_history(terminal_line);
		exec_prompt(d, terminal_line);
		//handle_splits(d, terminal_line);
	}
	free(terminal_line);
	free(prompt_msg);
	return (1);
}
