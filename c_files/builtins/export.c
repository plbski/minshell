/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:09:44 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/26 12:40:04 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	reorder_dblst(t_dblist *list)
{
	t_dblist	*db_b;
	char		*tmp;
	int			min_len;

	while (list->next)
	{
		db_b = list->next;
		while (db_b->next)
		{
			if (!list->content || !db_b->content)
				continue ;
			min_len = ft_strlen((char *)list->content);
			if (min_len > ft_strlen((char *)db_b->content))
				min_len = ft_strlen((char *)db_b->content);
			if (ft_strncmp((char *)list->content, (char *)db_b->content, \
				min_len) > 0)
			{
				tmp = list->content;
				list->content = db_b->content;
				db_b->content = tmp;
			}
			db_b = db_b->next;
		}
		list = list->next;
	}
}

int	export(t_data *d, char *arg, char **flags, int tmp_mem)
{
	char		*key;
	char		*value;
	t_dblist	*new_node;

	(void)flags;
	if (!arg)
	{
		reorder_dblst(dblst_first(d->env_list));
		env(d, NULL, NULL, 0);
		return (1);
	}
	key = truncate_at_end(arg, '=');
	value = ft_strchr(arg, '=') + 1;
	if (!set_key_value(d, d->env_list, key, value))
	{
		new_node = dblst_new(ft_str_mega_join(key, "=", value, NULL));
		if (!new_node->content)
			custom_exit(d, "No prompt for node", NULL, 1);
		if (tmp_mem)
			dblst_add_back(&d->env_list, new_node);
		else if (!set_key_value(d, d->tmp_list, key, value))
			dblst_add_back(&d->tmp_list, new_node);
	}
	update_environ(d);
	return (1);
}
