/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:18:16 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/04 16:03:25 by giuliovalen      ###   ########.fr       */
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
char	*get_env_value(t_data *d, t_dblist *list, char *key)
{
	t_dblist	*element;
	char		*content_copy;
	char		*no_key;
	char		*value;

	if (!list)
		return (NULL);
	element = get_dblst_at_key(list, key);
	if (!element || !element->content)
		return (NULL);
	content_copy = ms_strdup(d, element->content);
	no_key = ft_remove_prefix(d, content_copy, key);
	if (!no_key)
		custom_exit(d, "env key alloc", NULL, EXIT_FAILURE);
	value = ft_remove_prefix(d, no_key, "=");
	if (!value)
		custom_exit(d, "env value alloc", NULL, EXIT_FAILURE);
	return (free(content_copy), free(no_key), value);
}

void	update_variable(t_data *d, t_dblist *list, char **data_var, char *key_name)
{
	char	*var;

	var = get_env_value(d, list, key_name);
	if (var && (!*data_var || !cmp_str(d->home_wd, *data_var)))
	{
		safe_free(*data_var);
		*data_var = var;
	}
}

int	update_env_variables(t_data *d)
{
	char	*debug;

	debug = get_env_value(d, d->env_list, "deb");
	if (debug)
	{
		debug = ft_remove_prefix(d, debug, "=");
		d->debug_mode = ft_atoi(debug);
		free(debug);
	}
	update_variable(d, d->env_list, &d->home_wd, "HOME");
	update_variable(d, d->env_list, &d->logname, "LOGNAME");
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
		return (custom_exit(d, "Node alloc failed", NULL, EXIT_FAILURE));
	if (element->content)
		free(element->content);
	element->content = new_line;
	return (1);
}
