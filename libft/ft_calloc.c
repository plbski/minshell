/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:38:52 by gvalente          #+#    #+#             */
/*   Updated: 2024/10/10 15:48:49 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*bites;

	if (count == 0 || size == 0)
		return (malloc(0));
	bites = malloc(count * size);
	if (bites == NULL)
		return (NULL);
	ft_bzero(bites, count * size);
	return (bites);
}
