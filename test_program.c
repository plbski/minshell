/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 01:23:31 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/26 16:11:10 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"

int	main(int argc, char *argv[])
{
	int	i;
	char	**error;
	printf("Program successfully launched. argc = %d\n", argc);
	i = -1;
	while (++i < argc)
		printf("arg[%d] = %s\n", i, argv[i]);
	
	i = 30;
	while (i > 0)
	 continue ;
	return (0);
}
