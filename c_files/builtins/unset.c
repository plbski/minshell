/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:26:40 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/26 12:39:35 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	unset(t_data *d, char *arg, char **flags, int status)
{
	t_dblist	*element;

	(void)flags;
	(void)status;
	element = get_dblst_at_key(d->env_list, arg);
	if (!element)
		return (0);
	dblst_delone(element, free);
	return (1);
}
