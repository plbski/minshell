/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 01:23:31 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/26 01:26:10 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"

int	main(int argc, char *argv[])
{
	printf("Program successfully launched. argc > %d\n", argc);
	while (argc--)
		printf("arg[%d] = %s\n", argc, argv[argc]);
	return (0);
}
