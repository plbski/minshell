/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 00:14:18 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/21 21:29:00 by gvalente         ###   ########.fr       */
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
	value = ft_remove_prefix(content_copy, key);
	return (value);
}

void	init_env_variables(t_data *d)
{
	if (d->env_list)
		dblst_clear(&d->env_list, free);
	d->env_list = arr_to_dblst((void **)d->environ);
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

void	show_env(t_data *d)
{
	dblst_print_list(d->env_list);
}

void	update_environ(t_data *d)
{
	char		**new_env;

	new_env = list_to_arr(d->env_list);
	if (!new_env)
		return ;
	d->environ = new_env;
	for (int i = 0; d->environ[i]; i++)
		printf("%s\n", d->environ[i]);
}

void	export_env(t_data *d, char *prompt)
{
	char		*new_content;
	char		*key;
	t_dblist	*new_node;
	t_dblist	*element;

	if (!get_char_occurence(prompt, '='))
		return ;
	key = truncate_at_end(prompt, '=');
	if (!key)
		return ;
	element = get_dblst_at_key(d->env_list, key);
	if (element)
	{
		free(element->content);
		element->content = ft_strdup(prompt);
		update_env_variables(d);
		update_environ(d);
		return ;
	}
	new_content = ft_strdup(prompt);
	new_node = dblst_new(new_content);
	dblst_add_back(&d->env_list, new_node);
	update_environ(d);
}
