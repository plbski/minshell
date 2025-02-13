/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:09:44 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/12 21:21:19 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	is_valid_key(char *key)
{
	int	i;

	if (!key)
		return (0);
	i = -1;
	while (key[++i])
		if (!ft_isalnum(key[i]) && !(key[i] == '+' && !key[i + 1]))
			return (0);
	return (1);
}

static void	handle_joined_arg(t_data *d, char *key, char *value)
{
	char		*new_value;
	t_dblist	*node;

	key[ft_strlen(key) - 1] = '\0';
	node = get_dblst_at_key(d->env_list, key);
	if (!node)
		node = get_dblst_at_key(d->tmp_list, key);
	if (!node)
		node = get_dblst_at_key(d->var_list, key);
	if (!node)
		return ;
	if (node->content)
		new_value = ft_strjoin(node->content, value);
	else
		new_value = ft_str_mega_join(key, "=", value, NULL);
	if (!new_value)
		custom_exit(d, "alloc for joined export arg", NULL, EXIT_FAILURE);
	if (node->content)
		safe_free(node->content);
	node->content = new_value;
}

static int	handle_no_value_export(t_data *d, char *arg, int tmp_mem)
{
	t_dblist	*var_node;
	char		*new_content;

	if (!is_valid_key(arg))
		return (printf("msh: export: %s: invalid option\n", arg), 127);
	if (get_dblst_node(d->env_list, arg))
		return (FCT_SUCCESS);
	if (!tmp_mem)
	{
		var_node = get_dblst_at_key(d->var_list, arg);
		if (var_node)
			new_content = ms_strdup(d, var_node->content);
		else
			new_content = ms_strdup(d, arg);
		if (get_dblst_node(d->env_list, new_content))
		{
			free(new_content);
			return (FCT_SUCCESS);
		}
		dblst_add_back(&d->env_list, dblst_new(new_content));
		update_environ(d);
	}
	else if (!get_dblst_node(d->var_list, arg))
		dblst_add_back(&d->var_list, dblst_new(ms_strdup(d, arg)));
	return (FCT_SUCCESS);
}

static int	exec_export(t_data *d, char *arg, int tmp_mem)
{
	char		*key;
	char		*value;
	t_dblist	*new_node;

	if (!chr_amnt(arg, '='))
		return (handle_no_value_export(d, arg, tmp_mem));
	key = truncate_at_end(arg, '=');
	if (!is_valid_key(key))
		return (safe_free(key), \
			printf("msh: %s: command not found\n", arg), CMD_NOT_FOUND);
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
		else if (!set_key_value(d, d->var_list, key, value))
			dblst_add_back(&d->var_list, new_node);
	}
	return (safe_free(key), update_environ(d), FCT_SUCCESS);
}

int	export(t_data *d, char *arg, char **flags, int tmp_mem)
{
	int			i;
	t_dblist	*env_copy;
	int			ret_value;

	if (!arg)
	{
		env_copy = arr_to_dblst((void **)d->environ);
		reorder_dblst(dblst_first(env_copy));
		dblst_print_list(env_copy, 1);
		dblst_clear(&env_copy, free);
		return (FCT_SUCCESS);
	}
	ret_value = exec_export(d, arg, tmp_mem);
	if (ret_value != FCT_SUCCESS)
		return (ret_value);
	i = -1;
	while (flags && flags[++i])
	{
		ret_value = exec_export(d, flags[i], tmp_mem);
		if (ret_value != FCT_SUCCESS)
			return (ret_value);
	}
	return (FCT_SUCCESS);
}
