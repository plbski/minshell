/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:21:54 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/28 15:57:15 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	*expand_special_segment(t_data *d, char *split, int *i)
{
	char	*str;

	str = NULL;
	if (!split[*i + 1])
		str = ft_strdup("$");
	else if (split[*i + 1] == '$')
		str = ft_itoa(getpid());
	else if (split[*i + 1] == '?')
		str = ft_itoa(d->last_exit_status);
	else if (split[*i + 1] == '0')
		str = ft_strdup(START_ANIM_TEXT);
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
	var_name = copy_until_char(d, split, &start, "$?'\"");
	value = get_env_value(d, d->env_list, var_name);
	!value && (value = get_env_value(d, d->tmp_list, var_name));
	free(var_name);
	(*i)--;
	if (!value)
		return (NULL);
	str = ft_strdup(value);
	if (!str)
		custom_exit(d, "malloc in token expansion", NULL, EXIT_FAILURE);
	return (str);
}

char	*expand_split(t_data *d, char *split, int len, int i)
{
	char	**spl_values;
	char	*new_str;
	int		spl_index;

	spl_index = 0;
	spl_values = malloc(sizeof(char *) * len);
	i = 0;
	while (i < len && split[i])
	{
		if (split[i] == '$' && is_in_quote(split, i) != 1)
		{
			new_str = expand_segment(d, split, &i);
			new_str && (spl_values[spl_index++] = new_str);
		}
		else
		{
			split[i] == '$' && (i++);
			spl_values[spl_index++] = copy_until_char(d, split, &i, "$");
		}
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
		splits_amount = get_char_occurence(splits[i], '$');
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
