/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:09:44 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/19 18:08:45 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static char	*get_valid_key(t_data *d, char *arg)
{
	int		i;
	int		break_index;

	break_index = -1;
	i = -1;
	while (arg && arg[++i])
	{
		if (i == 0 && !ft_isalpha(arg[i]) && !char_in_str(arg[i], "_\'\""))
			break ;
		else if (i > 0 && break_index == -1 && \
!ft_isdigit(arg[i]) && !ft_isalpha(arg[i]) && !char_in_str(arg[i], "+=_\'\""))
			break ;
		else if (arg[i] == '=' && break_index == -1)
			break_index = i;
		if (arg[i] == '+' && arg[i + 1] != '=' && break_index == -1)
			break ;
	}
	if (arg && i > 0 && !arg[i])
	{
		if (break_index != -1)
			return (ms_strndup(d, arg, break_index));
		return (ms_strdup(d, arg));
	}
	return (printf("msh: export: \'%s\': not a valid identifier\n", arg), NULL);
}

static void	handle_joined_arg(t_data *d, char *key, char *value, int tmp_mem)
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
	{
		node = dblst_new(NULL);
		if (tmp_mem)
			dblst_add_back(&d->var_list, node);
		else
			dblst_add_back(&d->env_list, node);
	}
	if (node->content)
		new_value = ft_strjoin(node->content, value);
	else
		new_value = ft_megajoin(key, "=", value, NULL);
	if (!new_value)
		custom_exit(d, "alloc for joined export arg", NULL, EXIT_FAILURE);
	setstr(d, (char **)&node->content, new_value);
}

static int	handle_no_value_export(t_data *d, char *key, int tmp_mem)
{
	t_dblist	*var_node;
	char		*new_content;

	if (get_dblst_node(d->env_list, key))
		return (FCT_OK);
	if (!tmp_mem)
	{
		var_node = get_dblst_at_key(d->var_list, key);
		if (var_node)
			new_content = ms_strdup(d, var_node->content);
		else
			new_content = ms_strdup(d, key);
		if (get_dblst_node(d->env_list, new_content))
		{
			free(new_content);
			return (FCT_OK);
		}
		dblst_add_back(&d->env_list, dblst_new(new_content));
		update_environ(d);
	}
	else if (!get_dblst_node(d->var_list, key))
		dblst_add_back(&d->var_list, dblst_new(ms_strdup(d, key)));
	return (FCT_OK);
}

static int	exec_export(t_data *d, char *arg, int tmp_mem)
{
	char		*key;
	char		*value;
	t_dblist	*new_node;

	key = get_valid_key(d, arg);
	if (!key)
		return (CMD_NOT_FOUND);
	if (!chr_amnt(arg, '='))
		return (handle_no_value_export(d, key, tmp_mem));
	value = ft_strchr(arg, '=') + 1;
	if (key[ft_strlen(key) - 1] == '+')
		handle_joined_arg(d, key, value, tmp_mem);
	else if (!set_key_value(d, d->env_list, key, value))
	{
		new_node = dblst_new(ft_megajoin(key, "=", value, NULL));
		if (!new_node->content)
			custom_exit(d, "content for node", NULL, EXIT_FAILURE);
		if (!tmp_mem)
			dblst_add_back(&d->env_list, new_node);
		else if (!set_key_value(d, d->var_list, key, value))
			dblst_add_back(&d->var_list, new_node);
	}
	return (safe_free(key), update_environ(d), FCT_OK);
}

int	export(t_data *d, char *arg, char **flags, int tmp_mem)
{
	int			i;
	int			ret_value;
	int			env_value;

	env_value = FCT_OK;
	if (!arg)
	{
		reorder_dblst(dblst_first(d->env_list));
		dblst_print_list(d->env_list, 1);
		return (FCT_OK);
	}
	ret_value = exec_export(d, arg, tmp_mem);
	if (ret_value != FCT_OK)
		env_value = ret_value;
	i = -1;
	while (flags && flags[++i])
	{
		if (exec_export(d, flags[i], tmp_mem) != FCT_OK)
			env_value = CMD_NOT_FOUND;
	}
	return (env_value);
}
