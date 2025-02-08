/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:54:36 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/06 18:50:39 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"

void	render_str(t_data *d)
{
	int	i;

	i = -1;
	while (d->str[++i])
	{
		if (d->str[i] == 'P')
			printf("%s_", BLUE);
		else if (d->plr.shield && i + d->size.x + 1 < d->len && d->str[i + d->size.x + 1] == 'P')
			printf("%s_", GREEN);
		else if (d->str[i] == '|' || d->str[i] == '\\' || d->str[i] == '/')
			printf("%s%c", d->plr.pow ? RED : BLUE, d->str[i]);
		else if (d->str[i] == '.')
			printf("%s*", RED);
		else if (d->str[i] == '*')
			printf("%s.", YELLOW);
		else if (d->str[i] == LASER_LEFTOVER)
			printf("%s|", BLUE);
		else if (char_cmp(BONUSES, d->str[i]))
			printf("%s%c", d->str[i] >= 'a' ? GREEN : YELLOW, d->str[i]);
		else if (d->str[i] == '>' || d->str[i] == '<')
			printf("%s%s", RED, PROMPT_SQARE);
		else
			printf("%c", d->str[i]);
		printf("%s", RESET);
	}
}

void	render_if_one(char *label, int value)
{
	if (value)
		printf("| %s %d |", label, value);
}

void	render_matrix(t_data *d, int max_score)
{
	int	slp_time;
	int	x;

	system("clear");
	printf("SCORE %d MAX %d\n", d->score, max_score);
	x = -1;
	while (++x < d->size.x)
		printf("_");
	printf("\n");
	render_str(d);
	x = -1;
	while (++x < d->size.x)
		printf("_");
	printf("\n");
	render_if_one("ATK_SPD", d->plr.atk_spd);
	render_if_one("POW", d->plr.pow);
	render_if_one("BOMB", d->plr.bomb);
	render_if_one("LIFE", d->plr.life);
	render_if_one("MULT", d->plr.mult);
	render_if_one("SHIELD", d->plr.shield);
	render_if_one("SPD", d->plr.speed);
	render_if_one("PROJ", d->plr.prj_type);
	printf("\n");

	slp_time = 30000 - (d->time);
	slp_time <= 20000 && (slp_time = 20000);
	usleep(slp_time);
}
