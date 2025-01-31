/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 00:14:18 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/30 20:40:58 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	env(t_data *d, char *arg, char **flags, int has_prefix)
{
	(void)arg;
	(void)flags;
	dblst_print_list(d->env_list, has_prefix);
	return (FCT_SUCCESS);
}
