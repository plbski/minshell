/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:16:24 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/26 12:38:16 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	clear(t_data *d, char *arg, char **flags, int status)
{
	(void)d;
	(void)arg;
	(void)flags;
	(void)status;
	system("clear");
	return (1);
}
