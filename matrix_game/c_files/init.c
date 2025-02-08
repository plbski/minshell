/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 20:07:10 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/06 18:43:34 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"

void	handle_end(int input_return, int score, int max_score, char **env)
{
	int		record_file;
	char	buffer[12];
	int		len;
	char	c;

	if (input_return != 2)
	{
		set_nonblocking_input(1);
		c = getchar();
		while (c == -1)
			c = getchar();
		if (c == 'q')
			return ;
	}
	if (score > max_score)
	{
		record_file = open("matrix_scores.txt", \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		len = snprintf(buffer, 12, "%d\n", score);
		write(record_file, buffer, len);
		close(record_file);
	}
	execve("./matrix", NULL, env);
}

int	load_max_score(void)
{
	int		score_file;
	char	score_buff[12];

	score_file = open("matrix_scores.txt", O_RDONLY);
	if (score_file > 0)
	{
		read(score_file, &score_buff, 12);
		return (ft_atoi(score_buff));
	}
	return (0);
}

char	*init_matrix(t_data d, int *str_len)
{
	char	*matrix;
	int		i;
	int		len;

	len = ((d.size.x + 1) * d.size.y) + 1;
	matrix = malloc(len + 1);
	if (!matrix)
		exit(0);
	i = -1;
	while (++i < len)
	{
		if (i % (d.size.x + 1) == 0)
			matrix[i] = '\n';
		else
			matrix[i] = ' ';
	}
	matrix[i] = '\0';
	*str_len = i;
	return (matrix);
}

void	init_data(t_data *d)
{
	d->size = get_v2(100, 40);
	d->score = 0;
	d->game_over = 0;
	d->plr.pos = get_v2(GRID_X * ((d->size.x / GRID_X) / 2) + 3, d->size.y - 1);
	d->plr.index = ((d->size.x + 1) * d->plr.pos.y + d->plr.pos.x);
	d->plr.trg_x = -1;
	d->plr.atk_spd = 1;
	d->plr.mv = get_v2(GRID_X / 3, GRID_X / 3);
	d->plr.prj_type = base;
	d->plr.life = 1;
	d->plr.bomb = 0;
	d->plr.mult = 1;
	d->plr.prj_type_count = 0;
	d->plr.shield = 0;
	d->plr.proj = NULL;
	d->plr.speed = 1;
	d->plr.pow = 0;
}

int	main(int argc, char *argv[], char **env)
{
	t_data	d;

	srand(time(0));
	init_data(&d);
	if (argc >= 2)
		d.size.x = ft_atoi(argv[1]);
	if (argc >= 3)
		d.size.y = ft_atoi(argv[2]);
	d.str = init_matrix(d, &d.len);
	matrix_loop(&d, env);
	free(d.str);
}
