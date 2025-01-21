/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:35:21 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/21 16:07:59 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	safe_free(void *line)
{
	if (line)
		free(line);
}

int	free_void_array(void ***item)
{
	int	free_count;

	if (item == NULL || *item == NULL)
		return (0);
	free_count = 0;
	while ((*item)[free_count] != NULL)
	{
		free((*item)[free_count]);
		(*item)[free_count] = NULL;
		free_count++;
	}
	free(*item);
	*item = NULL;
	return (free_count);
}
