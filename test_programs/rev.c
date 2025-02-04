/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 08:44:32 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/04 10:15:31 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void	print_rev(char *buffer)
{
	int		numbers[99999];
	int		count;
	int		i;
	char	*token;

	count = 0;
	token = strtok(buffer, " ");
	while (token)
	{
		numbers[count++] = atoi(token);
		token = strtok(NULL, " ");
	}
	i = count - 1;
	while (i >= 0)
		printf("%d ", numbers[i--]);
	printf("\n");
}

int	main(int argc, char *argv[])
{
	char	buffer[99999];

	if (argc < 2)
	{
		if (!fgets(buffer, 99999, stdin))
			return (1);
		buffer[strcspn(buffer, "\n")] = 0;
	}
	else
	{
		strncpy(buffer, argv[1], 99999);
		buffer[99999 - 1] = '\0';
	}
	print_rev(buffer);
	return (0);
}
