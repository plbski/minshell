/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_entities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:57:39 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/06 18:54:37 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"

int	update_mob(t_data *d, int i)
{
	int	new_index;
	int	return_val;

	return_val = 0;
	new_index = i + d->size.x + 1;
	if (new_index < d->len && d->str[new_index] != '\n')
	{
		return_val = 1;
		if (d->str[new_index] == 'P')
		{
			if (d->plr.shield)
				d->plr.shield--;
			else if (d->plr.life)
				d->plr.life--;
			else
				d->game_over = 1;
			return (0);
		}
		d->str[new_index] = d->str[i];
		if (new_index + d->size.x + 1 < d->len && r_range(0, 50) == 0)
			d->str[new_index + d->size.x + 1] = '.';
	}
	d->str[i] = ' ';
	return (return_val);
}

int	update_collectible(t_data *d, int i, char c)
{
	int	is_big;

	if (d->time % 3 != 0)
		return (1);
	d->str[i] = ' ';
	if (i + d->size.x + 1 > d->len)
		return (0);
	if (d->str[i + (d->size.x + 1)] == 'P')
	{
		is_big = 0;
		if (c >= 'A' && c <= 'Z')
		{
			is_big = 1;
			c += 32;
		}
		if (c == BONUS_SCORE)
			d->score += 10 * (1 + (is_big * 3));
		else if (c == BONUS_SPEED && d->plr.speed < GRID_X)
			d->plr.speed += 1 * (1 + (is_big * 3));
		else if (c == BONUS_ATKSPD)
			d->plr.atk_spd += 1 * (1 + (is_big * 3));
		else if (c == BONUS_BOMB)
			d->plr.bomb += 1 * (1 + (is_big * 3));
		else if (c == BONUS_LIFE)
			d->plr.life += 1 * (1 + (is_big * 3));
		else if (c == BONUS_MULT)
			d->plr.mult += 1 * (1 + (is_big * 3));
		else if (c == BONUS_SHIELD)
			d->plr.shield += 1 * (1 + (is_big * 3));
	}
	else if (d->str[i + (d->size.x + 1)] != '\n')
		d->str[i + (d->size.x + 1)] = c;
	return (1);
}

int	update_stars(t_data *d, int i)
{
	if (r_range(0, 500) == 0)
	{
		d->str[i] = ' ';
		return (0);
	}
	return (1);
}

void	update_plr(t_data *d, t_player *plr)
{
	int		x;

	if (plr->mv.x && plr->index + plr->mv.x > 0 && \
		plr->index + plr->mv.x < d->len)
	{
		x = 0;
		while (x++ < PLR_SIZE)
			d->str[plr->index + x] = ' ';
		if (plr->trg_x != -1 && plr->trg_x > plr->index)
		{
			plr->index = MIN(plr->trg_x, plr->index + plr->mv.x);
			if (plr->mv.x / 4 - plr->speed >= 1)
				plr->mv.x--;
		}
		else if (plr->trg_x != -1 && plr->trg_x < plr->index)
		{
			plr->index = MAX(plr->trg_x, plr->index - plr->mv.x);
			if (plr->mv.x / 4 >= 1)
				plr->mv.x--;
		}
		if (plr->index == plr->trg_x)
		{
			plr->trg_x = -1;
			plr->mv.x = GRID_X / 3;
		}
		x = 0;
	}
}

void	update_str(t_data *d, int *o_count, int *mob_count, int *star_count)
{
	int	i;

	i = d->len;
	while (--i >= 0)
	{
		if (d->str[i] == LASER_LEFTOVER)
			d->str[i] = ' ';
		if (d->str[i] == LASER_PRJ && i - d->size.x - 1 > 0)
		{
			if (d->str[i - d->size.x - 1] == '>' || d->str[i - d->size.x - 1] == '<')
				d->str[i - d->size.x - 1] = ' ';
			else
				d->str[i - d->size.x - 1] = LASER_PRJ;
		}
		if (d->str[i] == '*')
			(*star_count) += update_stars(d, i);
		else if (d->str[i] == '.')
			update_mob_prj(d, i);
		else if (char_cmp(BONUSES, d->str[i]))
			(*o_count) += update_collectible(d, i, d->str[i]);
		else if ((d->str[i] == '>' || d->str[i] == '<') && d->time % 2 == 0)
			(*mob_count) += update_mob(d, i);
	}
	i = -1;
	while (d->str[++i])
		if (d->str[i] == LASER_PRJ)
			d->str[i] = LASER_LEFTOVER;
}
