/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tools2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:25:15 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/31 21:28:41 by giuliovalen      ###   ########.fr       */
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

char	*copy_until_char(t_data *d, char *str, int *start, const char *set)
{
	char	*copy;
	int		i;
	int		j;
	int		stop_index;

	if (*start >= ft_strlen(str) || str[*start] == '\0')
		return (NULL);
	i = *start;
	while (str[i] && !char_in_str(str[i], set))
		i++;
	stop_index = i;
	copy = malloc(stop_index - *start + 1);
	if (!copy)
		custom_exit(d, "alloc fail in token copy", NULL, EXIT_FAILURE);
	i = *start;
	j = -1;
	while (++j < stop_index - *start)
		copy[j] = str[i + j];
	copy[stop_index - *start] = '\0';
	*start = stop_index - 1;
	return (copy);
}

void	remove_chars(t_data *d, char **txt, const char *to_remove)
{
	char	*new_str;
	int		new_len;
	int		i;
	int		j;

	new_len = 0;
	i = -1;
	while ((*txt)[++i])
		if (!char_in_str((*txt)[i], to_remove))
			new_len++;
	if (new_len == ft_strlen(*txt))
		return ;
	new_str = malloc(new_len + 1);
	if (!new_str)
		custom_exit(d, "alloc in remove chars", NULL, EXIT_FAILURE);
	j = -1;
	i = -1;
	while ((*txt)[++i])
		if (!char_in_str((*txt)[i], to_remove))
			new_str[++j] = (*txt)[i];
	new_str[++j] = '\0';
	free(*txt);
	*txt = new_str;
}

char	*contract_str(t_data *d, char **strs)
{
	int		i;
	int		j;
	int		total_len;
	int		str_index;
	char	*str;

	total_len = 0;
	i = -1;
	while (strs[++i])
		total_len += ft_strlen(strs[i]);
	str = malloc(total_len + 1);
	if (!str)
		custom_exit(d, "alloc for contracted str", NULL, EXIT_FAILURE);
	str_index = 0;
	i = -1;
	while (strs[++i])
	{
		j = -1;
		while (strs[i][++j])
			str[str_index++] = strs[i][j];
	}
	str[str_index] = '\0';
	return (str);
}

int	cmp_str(const char *a, const char *b)
{
	int	len_a;
	int	len_b;
	int	i;

	if (!a || !b)
		return (0);
	len_a = ft_strlen(a);
	len_b = ft_strlen(b);
	if (len_a != len_b)
		return (0);
	i = -1;
	while (++i < len_a)
	{
		if (a[i] != b[i])
			return (0);
	}
	return (1);
}
