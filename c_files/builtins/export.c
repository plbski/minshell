/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:09:44 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/24 13:58:39 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	export(t_data *d, char *arg, char *flags, int status)
{
	t_dblist	*new_node;
	t_dblist	*element;

	(void)status;
	if (!arg)
	{
		reorder_dblst(dblst_first(d->env_list));
		env(d, NULL, NULL, 1);
		return (1);
	}
	element = get_dblst_at_key(d->env_list, arg);
	if (element)
	{
		free(element->content);
		element->content = flags;
		update_env_variables(d);
		update_environ(d);
		return (1);
	}
	new_node = dblst_new(flags);
	dblst_add_back(&d->env_list, new_node);
	update_environ(d);
	return (1);
}
