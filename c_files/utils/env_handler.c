/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:18:16 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/26 12:25:42 by giuliovalen      ###   ########.fr       */
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

//		Value is a copy and must be freed after use
char	*get_env_value(t_data *d, char *key)
{
	t_dblist	*element;
	char		*content_copy;
	char		*no_key;
	char		*value;

	if (!d->env_list)
		return (NULL);
	element = get_dblst_at_key(d->env_list, key);
	if (!element || !element->content)
		return (NULL);
	content_copy = ft_strdup(element->content);
	if (!content_copy)
		return (NULL);
	no_key = ft_remove_prefix(content_copy, key);
	if (!no_key)
		return (NULL);
	value = ft_remove_prefix(no_key, "=");
	if (!value)
		return (NULL);
	return (free(content_copy), free(no_key), value);
}

void	update_env_list(t_data *d, char **env)
{
	if (d->env_list)
		dblst_clear(&d->env_list, free);
	d->env_list = arr_to_dblst((void **)env);
	if (!d->env_list)
		custom_exit(d, "List alloc failed", NULL, 1);
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

int	set_key_value(t_data *d, t_dblist *list, char *key, char *value)
{
	t_dblist	*element;
	char		*new_line;

	element = get_dblst_at_key(list, key);
	if (!element)
		return (0);
	new_line = ft_str_mega_join(key, "=", value, NULL);
	if (!new_line)
		return (custom_exit(d, "Node alloc failed", NULL, 1));
	if (element->content)
		free(element->content);
	element->content = new_line;
	return (1);
}
