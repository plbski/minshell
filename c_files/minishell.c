/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:04:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/07 13:39:34 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	g_quit_in_heredoc;

int	main(int argc, char *argv[], char **env)
{
	t_data	data;

	(void)argv;
	data.debug_mode = argc > 1;
	setup_signal(0, 0);
	init_data(&data, env);
	printf("%s lv %d\n", START_ANIM_TEXT, data.shlvl);
	while (42)
	{
		if (!get_terminal_prompt(&data))
			break ;
	}
	custom_exit(&data, NULL, NULL, EXIT_SUCCESS);
	return (0);
}
