/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 00:14:18 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/14 13:43:45 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	env(t_data *d, char *arg, char **flags, int has_prefix)
{
	if (arg || flags)
	{
		ft_dprintf(2, "env: %s: No such file or directory\n", arg);
		return (FCT_FAIL);
	}
	if (!d->tmp_list)
		printf("msh: env: No such file or directory\n");
	dblst_print_list(d->tmp_list, has_prefix);
	return (FCT_SUCCESS);
}
