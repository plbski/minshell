/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:04:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/16 19:44:02 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	main()
{
	t_data	data;

	signal(SIGINT, handle_sigint);
	write_animated_txt(START_ANIM_TEXT, 30000, 100000);
	init_data(&data);
	while (data.status == running)
	{
		if (!get_terminal_prompt(&data))
			break ;
	}
	write_animated_txt(END_ANIM_TEXT, 10000, 0);
	return (0);
}
