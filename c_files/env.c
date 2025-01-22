/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 00:14:18 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/22 20:44:25 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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
	value = ft_remove_prefix(content_copy, key, 1);
	return (value);
}

void	update_env_list(t_data *d, char **env)
{
	if (d->env_list)
		dblst_clear(&d->env_list, free);
	d->env_list = arr_to_dblst((void **)env);
	if (!d->env_list)
		custom_exit(d, 0);
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

void	print_env(t_data *d)
{
	dblst_print_list(d->env_list);
}

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
