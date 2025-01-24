/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:18:16 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/24 14:02:20 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	update_environ(t_data *d)
{
	char		**new_env;

	new_env = list_to_arr(d->env_list);
	if (!new_env)
		return ;
	if (d->environ)
		free_void_array((void ***)&d->environ);
	d->environ = new_env;
}

char	*get_env_value(t_data *d, char *key)
{
	t_dblist	*element;
	char		*content_copy;
	char		*value;

	if (!d->env_list)
		return (NULL);
	element = get_dblst_at_key(d->env_list, key);
	if (!element || !element->content)
		return (NULL);
	content_copy = ft_strdup(element->content);
	value = ft_remove_prefix(content_copy, key);
	return (value);
}

void	update_env_list(t_data *d, char **env)
{
	if (d->env_list)
		dblst_clear(&d->env_list, free);
	d->env_list = arr_to_dblst((void **)env);
	if (!d->env_list)
		custom_exit(d, NULL, NULL, 0);
}

int	update_env_variables(t_data *d)
{
	if (d->home_wd)
		free(d->home_wd);
	d->home_wd = get_env_value(d, "HOME=");
	if (d->logname)
		free(d->logname);
	d->logname = get_env_value(d, "LOGNAME=");
	return (1);
}

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
