/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:04:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/21 12:50:54 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	main(void)
{
	t_data	data;

	setup_signal();
	write_animated_txt(START_ANIM_TEXT, 3000, 10000);
	init_data(&data);
	while (data.status == running)
	{
		if (!get_terminal_prompt(&data))
			break ;
	}
	return (0);
}
