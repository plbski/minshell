/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:10:07 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/06 18:42:15 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"

int	handle_input(t_data *d)
{
	char	c;

	set_nonblocking_input(1);
	if (read(STDIN_FILENO, &c, 1) > 0)
	{
		if (c == ' ')
			d->str[d->plr.index + (PLR_SIZE / 2) - d->size.x] = '|';
		else if (c == 'a' && d->plr.trg_x == -1 && d->plr.index - \
			GRID_X > d->len - d->size.x)
			d->plr.trg_x = d->plr.index - GRID_X;
		else if (c == 'd' && d->plr.trg_x == -1 && d->plr.index + GRID_X < d->len)
			d->plr.trg_x = d->plr.index + GRID_X;
		else if (c == 'q')
			return (0);
		else if (c == 'r')
			return (2);
		else if (c == 't')
			d->plr.prj_type = (d->plr.prj_type + 1) % (prj_type_count - 1);
		else if (c == 'p' || c == 'P' || c == '\n')
			while (getchar() == -1)
				continue ;
	}
	return (set_nonblocking_input(0), 1);
}
