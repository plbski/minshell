/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:04:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/16 18:52:08 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	g_quit_in_heredoc = 0;

static void	init_msh(t_data *d, char **env)
{
	setup_signal(0, 0);
	init_data(d, env);
	d->prv_input = get_last_line(d, d->history_wd);
	if (d->prv_input)
		d->prv_input[ft_strlen(d->prv_input) - 1] = '\0';
}

int	main(int argc, char *argv[], char **env)
{
	t_data	data;
	int		started;

	started = 1;
	(void)argv;
	data.debug_mode = argc > 1;
	init_msh(&data, env);
	while (42)
	{
		if (!process_input(&data, started))
			break ;
		started = 0;
	}
	custom_exit(&data, NULL, NULL, EXIT_SUCCESS);
	return (0);
}
