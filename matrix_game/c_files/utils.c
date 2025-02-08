/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:52:55 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/06 14:09:09 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"

t_vec2	get_v2(int x, int y)
{
	t_vec2	v2;

	v2.x = x;
	v2.y = y;
	return (v2);
}

int	char_cmp(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}

int	cmp_v2(t_vec2 a, t_vec2 b)
{
	return (a.x == b.x && a.y == b.y);
}

int	r_range(int min, int max)
{
	if (min >= max)
		return (min);
	return (min + rand() % (max - min));
}

int	ft_atoi(const char *str)
{
	int	res;
	int	i;
	int	is_minus;

	i = 0;
	is_minus = 1;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			is_minus = -1;
		i++;
	}
	while (str[i] && str[i] >= '1' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res *= is_minus, res);
}

void	set_nonblocking_input(int enable)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	if (enable)
	{
		t.c_lflag &= ~ICANON;
		fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
	}
	else
	{
		t.c_lflag |= ICANON;
		fcntl(STDIN_FILENO, F_SETFL, \
			fcntl(STDIN_FILENO, F_GETFL) & ~O_NONBLOCK);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}
