/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:26:40 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/12 14:11:06 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	remove_element(t_dblist **list, char *arg)
{
	t_dblist	*element;

	if (!*list)
		return (0);
	element = get_dblst_at_key(*list, arg);
	if (!element)
		return (0);
	if (!element->next)
		*list = NULL;
	dblst_delone(element, free);
	return (1);
}

static int	exec_unset(t_data *d, char *arg)
{
	int	has_unset;

	has_unset = 0;
	has_unset += remove_element(&d->env_list, arg);
	has_unset += remove_element(&d->tmp_list, arg);
	has_unset += remove_element(&d->var_list, arg);
	if (!has_unset)
		return (FCT_FAIL);
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
