/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:54:07 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/06 20:44:15 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"

void	init_bonus(t_data *d, int index)
{
	char	new_bonus;

	if (index < 0 || index > d->len || d->str[index] != ' ')
		return ;
	new_bonus = BONUSES[r_range(0, BONUSES_LEN / 2)];
	if (r_range(0, 5) == 0)
		new_bonus = BONUSES[r_range(BONUSES_LEN / 2 + 1, BONUSES_LEN - 1)];
	d->str[index] = new_bonus;
}

void	refill_entities(int o_count, int mob_count, int star_count, t_data *d)
{
	int		random_index;
	int		r_x;

	while (o_count++ < 2)
		init_bonus(d, r_range(1, (d->size.x - 1) / GRID_X) * GRID_X - 2);
	while (d->time % 2 == 0 && mob_count++ < 1 + d->time / 50)
	{
		r_x = r_range(1, (d->size.x - 1) / GRID_X);
		if (r_range(0, 2) == 0)
			d->str[GRID_X * r_x - 4] = '>';
		else
			d->str[GRID_X * r_x - 4] = '<';
	}
	while (star_count++ < 50)
	{
		random_index = r_range(1, d->len / 2);
		if (random_index < d->len && d->str[random_index] == ' ')
			d->str[random_index] = '*';
	}
}

int	update_game(t_data *d)
{
	int	o_count;
	int	star_count;
	int	mob_count;

	star_count = 0;
	o_count = 0;
	mob_count = 0;
	update_plr_prj(d, &d->plr);
	update_str(d, &o_count, &mob_count, &star_count);
	refill_entities(o_count, mob_count, star_count, d);
	return (!d->game_over);
}

int	handle_loop(t_data *d, int *input_return, int max_score)
{
	int		x;
	int		game_return;

	while (1)
	{
		x = 0;
		while (x++ < PLR_SIZE)
			d->str[d->plr.index + x] = 'P';
		game_return = update_game(d);
		render_matrix(d, max_score);
		if (!game_return)
			break ;
		*input_return = handle_input(d);
		update_plr(d, &d->plr);
		if (!*input_return)
			return (0);
		if (*input_return == 2)
			break ;
		d->time++;
	}
	return (1);
}

void	matrix_loop(t_data *d, char **env)
{
	int		input_return;
	int		max_score;

	input_return = 0;
	max_score = load_max_score();
	handle_loop(d, &input_return, max_score);
	handle_end(input_return, d->score, max_score, env);
}
