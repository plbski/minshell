/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:09:44 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/07 23:08:44 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static void	handle_joined_arg(t_data *d, char *key, char *value)
{
	char		*new_value;
	t_dblist	*node;

	key[ft_strlen(key) - 1] = '\0';
	node = get_dblst_at_key(d->env_list, key);
	if (!node)
		node = get_dblst_at_key(d->tmp_list, key);
	if (!node)
		return ;
	new_value = ms_strjoin(d, node->content, value);
	free(node->content);
	node->content = new_value;
}

static void	exec_export(t_data *d, char *arg, int tmp_mem)
{
	char		*key;
	char		*value;
	t_dblist	*new_node;

	if (!chr_amnt(arg, '='))
	{
		if (get_dblst_node(d->env_list, arg))
			return ;
		new_node = dblst_new(ms_strdup(d, arg));
		dblst_add_back(&d->env_list, new_node);
		return ;
	}
	key = truncate_at_end(arg, '=');
	value = ft_strchr(arg, '=') + 1;
	if (key[ft_strlen(key) - 1] == '+')
		handle_joined_arg(d, key, value);
	else if (!set_key_value(d, d->env_list, key, value))
	{
		new_node = dblst_new(ft_str_mega_join(key, "=", value, NULL));
		if (!new_node->content)
			custom_exit(d, "No prompt for node", NULL, 1);
		if (!tmp_mem)
			dblst_add_back(&d->env_list, new_node);
		else if (!set_key_value(d, d->tmp_list, key, value))
			dblst_add_back(&d->tmp_list, new_node);
	}
	safe_free(key);
	update_environ(d);
}

int	export(t_data *d, char *arg, char **flags, int tmp_mem)
{
	int			i;
	t_dblist	*env_copy;

	if (!arg)
	{
		env_copy = arr_to_dblst((void **)d->environ);
		reorder_dblst(dblst_first(env_copy));
		dblst_print_list(env_copy, 1);
		free_void_array((void ***)&env_copy);
		return (FCT_SUCCESS);
	}
	exec_export(d, arg, tmp_mem);
	i = -1;
	while (flags && flags[++i])
		exec_export(d, flags[i], tmp_mem);
	return (FCT_SUCCESS);
}
