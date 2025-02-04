/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:33:14 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/04 09:58:15 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int	r_range(int min, int max)
{
	if (max == min)
		return (max);
	if (max < min)
		return (-1);
	return (rand() % max - min);
}

int	main(int argc, char *argv[])
{
	int	nmb_len;

	srand(0);
	nmb_len = 5;
	if (argc == 2 && argv[1])
		nmb_len = atoi(argv[1]);
	while (nmb_len--)
		printf("%d ", (rand() % ((nmb_len + 1) * 2)) * (1 - (rand() % 2) * 2));
}
