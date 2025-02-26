/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 00:14:18 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/25 22:47:05 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

int	env(t_data *d, char *arg, char **flags, int has_prefix)
{
	if (arg || flags)
	{
		ft_dprintf(2, "env: %s: No such file or directory\n", arg);
		return (FCT_FAIL);
	}
	if (!d->env_list)
		ft_dprintf(2, "msh: env: No such file or directory\n");
	dblst_print_list(d->env_list, has_prefix);
	return (FCT_OK);
}
