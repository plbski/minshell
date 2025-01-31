/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 01:23:31 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/31 10:25:52 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// int	main(int argc, char *argv[])
// {
// 	t_data	d;

// 	if (argc <= 1)
// 		return (0);
// 	init_builtins_data(&d);
// 	printf("is valid: %d\n", validate_prmpt(&d, &argv[1]));
// 	tokenize_string(&d, argv[1]);
// 	return (1);
// }

int	main(int argc, char *argv[])
{
	int		i;
	char	c;

	printf("Program successfully launched. argc = %d\n", argc);
	i = -1;
	while (++i < argc)
		printf("arg[%d] = %s\n", i, argv[i]);
	printf("enter any key to exit\n");
	while (42)
	{
		c = getchar();
		if (c != -1)
			break ;
	}
	printf("exit code: %d\n", c);
	return (c);
}
