/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:07:36 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/14 14:38:02 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (perror("wrong arg count"), 1);
	printf("executing command: %s\n", argv[1]);
	return (0);
}
