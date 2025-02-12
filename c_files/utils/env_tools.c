/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:18:16 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/12 18:02:36 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	update_environ(t_data *d)
{
	char		**new_env;

	if (!d->env_list)
		custom_exit(d, "No env list to update", NULL, EXIT_FAILURE);
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
	char		*no_key;
	char		*value;

	if (!list)
		return (NULL);
	element = get_dblst_at_key(list, key);
	if (!element || !element->content)
		return (NULL);
	no_key = ft_remove_prefix(d, element->content, key);
	if (!no_key)
		custom_exit(d, "env key alloc", NULL, EXIT_FAILURE);
	value = ft_remove_prefix(d, no_key, "=");
	free(no_key);
	if (!value)
		custom_exit(d, "env value alloc", NULL, EXIT_FAILURE);
	return (value);
}

void	update_env_var(t_data *d, t_dblist *list, char **var, char *key)
{
	char	*new_var_value;

	new_var_value = get_env_value(d, list, key);
	if (new_var_value)
	{
		safe_free(*var);
		*var = new_var_value;
	}
	else if (!*var)
		*var = ms_strdup(d, "?");
}

int	update_env_variables(t_data *d)
{
	char	*debug;
	char	*tmp_debug;

	debug = get_env_value(d, d->var_list, "deb");
	if (debug)
	{
		tmp_debug = ft_remove_prefix(d, debug, "=");
		d->debug_mode = ft_atoi(tmp_debug);
		free(debug);
		free(tmp_debug);
	}
	else
		d->debug_mode = 0;
	update_env_var(d, d->env_list, &d->home_wd, "HOME");
	update_env_var(d, d->env_list, &d->logname, "LOGNAME");
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
