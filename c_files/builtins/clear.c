/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:16:24 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/26 13:54:22 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	clear(t_data *d _UNUSED, char *a _UNUSED, char **f _UNUSED, int st _UNUSED)
{
	system("clear");
	return (1);
}
