/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:26:40 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/12 12:56:24 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	exec_unset(t_data *d, char *arg)
{
	t_dblist	*element;

	element = get_dblst_at_key(d->env_list, arg);
	if (!element && d->tmp_list)
		element = get_dblst_at_key(d->tmp_list, arg);
	if (!element)
		return (FCT_FAIL);
	dblst_delone(element, free);
	return (FCT_SUCCESS);
}

int	unset(t_data *d, char *arg, char **flags, int status)
{
	int			ret_val;
	int			i;

	(void)status;
	ret_val = exec_unset(d, arg);
	i = -1;
	while (flags && flags[++i])
	{
		if (exec_unset(d, flags[i]) == FCT_SUCCESS)
			ret_val = FCT_SUCCESS;
	}
	if (ret_val == FCT_SUCCESS)
		update_environ(d);
	return (FCT_SUCCESS);
}
