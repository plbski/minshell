/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:04:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/21 21:29:12 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	main(int argc, char *argv[], char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	setup_signal();
	write_animated_txt(START_ANIM_TEXT, 3000, 10000);
	init_data(&data, env);
	while (data.status == running)
	{
		if (!get_terminal_prompt(&data))
			break ;
	}
	return (0);
}
