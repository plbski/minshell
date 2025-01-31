/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:04:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/31 18:57:39 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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
