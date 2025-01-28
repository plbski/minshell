/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:16:24 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/28 01:30:21 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	clear(t_data *d, char *a, char **f, int st)
{
	(void)d;
	(void)a;
	(void)f;
	(void)st;
	system("clear");
	return (FCT_SUCCESS);
}
