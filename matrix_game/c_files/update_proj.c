/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_proj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:46:50 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/06 19:01:47 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"

int	update_mob_prj(t_data *d, int i)
{
	int	new_index;

	d->str[i] = ' ';
	new_index = i + d->size.x + 1;
	if (new_index > d->len)
		return (0);
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
	d->str[new_index] = '.';
	return (1);
}

int	get_dir_to_mob(t_data *d, int index)
{
	int		i;
	t_vec2	mob_pos;
	t_vec2	proj_pos;
	t_vec2	closest_distance;
	int		closest_index;
	float	min_distance;
	t_vec2	distance;
	float	current_distance;

	closest_index = -1;
	min_distance = -1;
	proj_pos = get_v2(index % d->size.x, index / d->size.x);
	i = -1;
	while (d->str[++i])
	{
		if (d->str[i] == '>' || d->str[i] == '<' || d->str[i] == 'v')
		{
			mob_pos = get_v2(i % d->size.x, i / d->size.x);
			distance = get_v2(mob_pos.x - proj_pos.x, mob_pos.y - proj_pos.y);
			current_distance = abs(distance.x) + abs(distance.y);
			if (min_distance == -1 || current_distance < min_distance)
			{
				min_distance = current_distance;
				closest_distance = distance;
				closest_index = i;
			}
		}
	}
	if (closest_index != -1)
	{
		if (abs(closest_distance.y) >= abs(closest_distance.x))
			index -= d->size.x + 1;
		else
		{
			if (closest_distance.x > 0)
				index++;
			else if (closest_distance.x < 0)
				index--;
			index -= (d->size.x + 1);
		}
	}
	else
		index -= (d->size.x + 1);
	return (index);
}

int	update_proj(t_data *d, t_player *plr, t_proj *proj)
{
	int	new_index;

	new_index = proj->index;
	proj->dir == left_up && (new_index -= (d->size.x + 2));
	proj->dir == right_up && (new_index -= (d->size.x));
	proj->dir == up && (new_index -= (d->size.x + 1));
	if (proj->type == follow)
		new_index = get_dir_to_mob(d, proj->index);
	if (new_index < 0 || new_index > d->len - 1 || d->str[new_index] == '\n')
		return (0);
	else if (d->str[new_index] == '<' || \
		d->str[new_index] == '>' || d->str[new_index] == '.')
	{
		d->str[new_index] != '.' && (d->score++);
		d->str[new_index] = ' ';
		if (r_range(0, 2) == 0)
			init_bonus(d, new_index);
		if (!plr->pow)
			return (0);
	}
	if (d->time % proj->speed == 0)
	{
		if (d->str[proj->index] == '|' || d->str[proj->index] == '/' || d->str[proj->index] == '\\')
			d->str[proj->index] = ' ';
		proj->index = new_index;
		if (proj->type == laser)
		{
			d->str[proj->index] = LASER_PRJ;
			proj->active = 0;
		}
		else if (d->str[proj->index] == ' ')
			d->str[proj->index] = proj->dir == up ? '|' : proj->dir == left_up ? '\\' : '/';
	}
	return (1);
}

void	update_plr_prj(t_data *d, t_player *plr)
{
	t_proj	*proj;
	t_proj	*next_proj;

	if ((d->time % (30 / d->plr.atk_spd)) <= 0)
		launch_plr_proj(d, plr);
	proj = prj_head(plr->proj);
	while (proj)
	{
		next_proj = proj->next;
		if (!proj->active || !update_proj(d, plr, proj))
			remove_proj(plr, proj, d);
		proj = next_proj;
	}
}
