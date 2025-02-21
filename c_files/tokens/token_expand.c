/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:21:54 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/21 18:34:53 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

char	*expand_special_segment(t_data *d, char *split, int *i)
{
	char	*str;

	str = NULL;
	if (!split[*i + 1])
		str = ms_strdup(d, "$");
	else if (split[*i + 1] == '$')
		str = ft_itoa(getpid());
	else if (split[*i + 1] == '?')
		str = ft_itoa(d->last_exit);
	else if (split[*i + 1] == '0')
		str = ms_strjoin(d, d->msh_wd, "/minishell");
	else
		return (NULL);
	if (!str)
		custom_exit(d, "alloc for $", NULL, EXIT_FAILURE);
	(*i)++;
	return (str);
}

char	*expand_segment(t_data *d, char *split, int *i)
{
	int		start;
	char	*var_name;
	char	*value;
	char	*str;

	str = expand_special_segment(d, split, i);
	if (str)
		return (str);
	(*i)++;
	start = *i;
	while (split[*i] && (ft_isalnum(split[*i]) || split[*i] == '_'))
		(*i)++;
	var_name = copy_until_char(d, split, &start, "$?'\"./");
	value = get_env_value(d, d->env_list, var_name);
	if (!value)
		value = get_env_value(d, d->tmp_list, var_name);
	if (!value)
		value = get_env_value(d, d->var_list, var_name);
	free(var_name);
	(*i)--;
	if (!value)
		return (ms_strdup(d, ""));
	return (value);
}

char	*expand_split(t_data *d, char *split, int len, int i)
{
	char	**spl_values;
	char	*new_str;
	int		spl_index;

	spl_index = 0;
	spl_values = ms_malloc(d, sizeof(char *) * len);
	while (i < len && split[i])
	{
		if (split[i] == '$' && in_quote(split, i) != 1)
		{
			new_str = expand_segment(d, split, &i);
			if (new_str)
				spl_values[spl_index++] = new_str;
		}
		else if (split[i] == '$')
			spl_values[spl_index++] = copy_until_char(d, split, &i, "\'");
		else
			spl_values[spl_index++] = copy_until_char(d, split, &i, "$");
		i++;
	}
	spl_values[spl_index] = NULL;
	new_str = contract_str(d, spl_values);
	return (free_void_array((void ***)&spl_values), new_str);
}

void	expand_splits(t_data *d, char **splits)
{
	int		i;
	int		splits_amount;
	int		len;
	char	*new_split;

	i = -1;
	while (splits[++i])
	{
		len = ft_strlen(splits[i]);
		splits_amount = chr_amnt(splits[i], '$');
		if (!splits_amount || (splits_amount == len && splits_amount > 2))
			continue ;
		new_split = expand_split(d, splits[i], ft_strlen(splits[i]), 0);
		if (new_split)
		{
			free(splits[i]);
			splits[i] = new_split;
		}
	}
}

void	update_node_expansion(t_data *d, t_token *node)
{
	char	*new_name;

	if (!node->name)
		node->name = ms_strdup(d, "");
	if (!node->name[0])
		return ;
	if (node->name[0] == '~' && (!node->name[1] || node->name[1] == '/'))
		replace_strstr(d, &node->name, "~", d->home_wd);
	if (chr_amnt(node->name, '$'))
	{
		new_name = expand_split(d, node->name, ft_strlen(node->name), 0);
		if (new_name)
			setstr(d, &node->name, new_name);
		else
			setstr(d, &node->name, ms_strdup(d, ""));
	}
	remove_quotes(d, &node->name);
}
