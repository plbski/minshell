/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:03:58 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/13 18:33:11 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	*get_token_in_split(char *str, int *i)
{
	char	first;

	if (char_in_str(str[*i], "<>&|"))
	{
		first = str[(*i)++];
		if (str[*i] == first)
			return (char_join(first, str[(*i)++], '\0', '\0'));
		return (char_join(first, '\0', '\0', '\0'));
	}
	else if (char_in_str(str[*i], "()"))
		return (char_join(str[(*i)++], '\0', '\0', '\0'));
	return (NULL);
}

char	*get_new_split(char *str, int *i)
{
	char	*new_split;
	int		len;
	int		size;

	new_split = get_token_in_split(str, i);
	if (new_split)
		return (new_split);
	len = *i;
	while (str[len] && (is_in_quote(str, *i) || \
		!char_in_str(str[len], "()<>&| ")))
		len++;
	size = (len - *i + 1);
	new_split = malloc(size);
	len = 0;
	while (len < size - 1)
		new_split[len++] = str[(*i)++];
	new_split[len] = '\0';
	return (new_split);
}

char	**split_prompt(t_data *d, char *str)
{
	char	**splits;
	int		token_index;
	int		i;
	int		str_len;

	token_index = 0;
	str_len = ft_strlen(str);
	splits = malloc(sizeof(char *) * str_len);
	if (!splits)
		custom_exit(d, "alloc in split", NULL, EXIT_FAILURE);
	i = 0;
	while (i < str_len && str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		splits[token_index++] = get_new_split(str, &i);
	}
	splits[token_index] = NULL;
	return (splits);
}
