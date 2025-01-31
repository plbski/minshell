/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:09:44 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/31 16:39:19 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static void	exec_export(t_data *d, char *arg, int tmp_mem)
{
	char		*key;
	char		*value;
	t_dblist	*new_node;

	if (!chr_amnt(arg, '='))
		return ;
	key = truncate_at_end(arg, '=');
	value = ft_strchr(arg, '=') + 1;
	if (!set_key_value(d, d->env_list, key, value))
	{
		new_node = dblst_new(ft_str_mega_join(key, "=", value, NULL));
		if (!new_node->content)
			custom_exit(d, "No prompt for node", NULL, 1);
		if (!tmp_mem)
			dblst_add_back(&d->env_list, new_node);
		else if (!set_key_value(d, d->tmp_list, key, value))
			dblst_add_back(&d->tmp_list, new_node);
	}
	update_environ(d);
}

int	export(t_data *d, char *arg, char **flags, int tmp_mem)
{
	int	i;

	(void)flags;
	if (!arg)
	{
		reorder_dblst(dblst_first(d->env_list));
		env(d, NULL, NULL, 1);
		return (FCT_SUCCESS);
	}
	exec_export(d, arg, tmp_mem);
	i = -1;
	while (flags && flags[++i])
		exec_export(d, flags[i], tmp_mem);
	return (FCT_SUCCESS);
}
