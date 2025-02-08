/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proj.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:08:18 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/06 20:42:55 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"

void	launch_plr_proj(t_data *d, t_player *plr)
{
	t_proj	*tail;
	int		amount;
	t_dir	dir;
	int		prj_index;

	prj_index = plr->index - (d->size.x - 1) + 2;
	amount = 0;
	tail = prj_tail(plr->proj);
	if (!tail)
	{
		plr->proj = init_proj(NULL, prj_index, up, plr->prj_type);
		tail = plr->proj;
		amount++;
		plr->prj_type_count++;
	}
	while (amount < plr->mult)
	{
		if (plr->prj_type_count >= MAX_PLR_PRJ - 1)
			remove_proj(plr, prj_head(plr->proj), d);
		amount == 0 && (dir = up);
		amount == 1 && (dir = left_up) && (prj_index--);
		amount == 2 && (dir = right_up) && (prj_index++);
		amount > 2 && (dir = right_up) && (prj_index++);
		tail->next = init_proj(tail, prj_index, dir, plr->prj_type);
		tail = tail->next;
		amount++;
		plr->prj_type_count++;
	}
}

void	remove_proj(t_player *plr, t_proj *prj, t_data *d)
{
	if (prj->index > 0 && prj->index <= d->len)
		d->str[prj->index] = ' ';
	if (prj->next)
		prj->next->prv = prj->prv;
	if (prj->prv)
		prj->prv->next = prj->next;
	else
		plr->proj = prj->next;
	plr->prj_type_count--;
	free(prj);
}

t_proj	*prj_head(t_proj *prj)
{
	if (!prj)
		return (NULL);
	while (prj->prv)
		prj = prj->prv;
	return (prj);
}

t_proj	*init_proj(t_proj *prv, int index, t_dir dir, t_prj_type type)
{
	t_proj	*new_proj;

	new_proj = malloc(sizeof(t_proj));
	if (!new_proj)
	{
		printf("alloc for proj\n");
		exit(0);
	}
	new_proj->index = index;
	new_proj->active = 1;
	new_proj->time = 0;
	new_proj->type = type;
	new_proj->speed = 1;
	if (new_proj->type == follow)
		new_proj->speed = 2;
	if (new_proj->type == laser)
		new_proj->speed = 10;
	new_proj->dir = dir;
	new_proj->time_left = 100;
	new_proj->prv = prv;
	new_proj->next = NULL;
	return (new_proj);
}

t_proj	*prj_tail(t_proj *prj)
{
	if (!prj)
		return (NULL);
	while (prj->next)
		prj = prj->next;
	return (prj);
}
