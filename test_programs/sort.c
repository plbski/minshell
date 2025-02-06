/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plbuet <plbuet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 08:44:32 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/06 14:47:07 by plbuet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void	set_numbers(int *count, char *buffer, int **numbers)
{
	char	*token;

	*count = 0;
	token = strtok(buffer, " ");
	while (token)
	{
		(*numbers)[(*count)++] = atoi(token);
		token = strtok(NULL, " ");
	}
}

void	print_sort(int *numbers, int count)
{
	int		i;
	int		j;
	int		temp;

	i = -1;
	while (++i < count - 1)
	{
		j = -1;
		while (++j < count - i - 1)
		{
			if (numbers[j] > numbers[j + 1])
			{
				temp = numbers[j];
				numbers[j] = numbers[j + 1];
				numbers[j + 1] = temp;
			}
		}
	}
	i = -1;
	while (++i < count)
		printf("%d ", numbers[i]);
}

void	sort(char *buffer)
{
	int	count;
	int	*numbers;

	numbers = malloc(sizeof(int) * 99999);
	set_numbers(&count, buffer, &numbers);
	print_sort(numbers, count);
	free(numbers);
}

int	main(int argc, char *argv[])
{
	char	buffer[99999];

	printf("start test\n");
	if (argc < 2)
	{
		if (!fgets(buffer, 99999, stdin))
			return (1);
		printf("buffer : %s\n", buffer);
		buffer[strcspn(buffer, "\n")] = 0;
	}
	else
	{
		strncpy(buffer, argv[1], 99999);
		buffer[99999 - 1] = '\0';
	}
	sort(buffer);
	return (0);
}
