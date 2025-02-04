/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 01:23:31 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/04 09:41:04 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "stdlib.h"

int	main(int argc, char *argv[])
{
	int		i;
	char	c;

	printf("Program successfully launched: argc = %d\n", argc);
	i = -1;
	while (++i < argc)
		printf("arg[%d] = %s\n", i, argv[i]);
	printf("enter any key to exit\n");
	c = getchar();
	printf("exit code: %d\n", c);
	return (c);
}
