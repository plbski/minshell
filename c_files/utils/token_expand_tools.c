/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:21:54 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/28 13:01:38 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	is_in_quote(char *str, int index)
{
	int	i;
	int	in_double_quote;
	int	in_single_quote;

	in_double_quote = 0;
	in_single_quote = 0;
	i = 0;
	while (str[i] && i <= index)
	{
		if (str[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		i++;
	}
	if (in_double_quote)
		return (2);
	else if (in_single_quote)
		return (1);
	return (0);
}

char	*copy_until_char(t_data *d, char *str, int *start_index, char stop)
{
	char	*copy;
	int		i;
	int		j;
	int		stop_index;

	if (*start_index >= ft_strlen(str))
		return (NULL);
	i = *start_index;
	while (str[i] && str[i] != stop && str[i] != '$')
		i++;
	stop_index = i;
	copy = malloc(stop_index - *start_index + 1);
	if (!copy)
	{
		custom_exit(d, "alloc fail in token copy", NULL, EXIT_FAILURE);
		return (NULL);
	}
	i = *start_index;
	j = -1;
	while (++j < stop_index - *start_index)
		copy[j] = str[i + j];
	copy[stop_index - *start_index] = '\0';
	*start_index = stop_index - 1;
	return (copy);
}

char	*expand_segment(t_data *d, char *split, int *i, char *str)
{
	int		start;
	char	*var_name;
	char	*value;

	if (*i >= ft_strlen(split))
		return (NULL);
	if (split[*i] == '?')
	{
		str = ft_itoa(d->last_exit_status);
		if (!str)
			custom_exit(d, "malloc in token expansion", NULL, EXIT_FAILURE);
		return (str);
	}
	start = *i;
	while (split[*i] && (ft_isalnum(split[*i]) || split[*i] == '_'))
		(*i)++;
	var_name = copy_until_char(d, split, &start, '?');
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

char	*expand_special_segment(t_data *d, char *split, int *i, int split_len)
{
	char	*str;

	if (*i >= split_len)
		return (NULL);
	if (!(split[*i] == '$' && split[*i + 1] == '$'))
		return (NULL);
	(*i)++;
	str = ft_itoa(getpid());
	if (!str)
		custom_exit(d, "alloc for $$", NULL, EXIT_FAILURE);
	return (str);
}

void	expand_split(t_data *d, char **split, int splits_amounts, int len)
{
	char	**spl_values;
	int		i;
	char	*new_str;
	int		spl_index;

	spl_index = 0;
	spl_values = malloc(sizeof(char *) * (splits_amounts));
	i = -1;
	while (i < len && *split[++i])
	{
		new_str = expand_special_segment(d, *split, &i, len);
		if (new_str)
			spl_values[spl_index++] = new_str;
		else if (*split[i] == '$')
		{
			i++;
			new_str = expand_segment(d, *split, &i, NULL);
			new_str && (spl_values[spl_index++] = new_str);
		}
		else
			spl_values[spl_index++] = copy_until_char(d, *split, &i, '$');
	}
	spl_values[spl_index] = NULL;
	free(*split);
	*split = contract_str(d, spl_values);
	free_void_array((void ***)&spl_values);
}

void	expand_splits_values(t_data *d, char **splits)
{
	int	i;
	int	splits_amount;

	i = -1;
	while (splits[++i])
	{
		splits_amount = get_char_occurence(splits[i], '$');
		if (!splits_amount)
			continue ;
		expand_split(d, &splits[i], splits_amount * 3, ft_strlen(splits[i]));
	}
}
