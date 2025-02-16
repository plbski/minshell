/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:03:58 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/14 03:25:36 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	*get_token_in_split(t_data *d, char *str, int *i)
{
	char	first;
	char	*joined;

	joined = NULL;
	if (char_in_str(str[*i], "<>&|"))
	{
		first = str[(*i)++];
		if (str[*i] == first)
			joined = char_join(first, str[(*i)++], '\0', '\0');
		else
			joined = char_join(first, '\0', '\0', '\0');
		if (!joined)
			custom_exit(d, "alloc of split token failed", NULL, EXIT_FAILURE);
	}
	else if (char_in_str(str[*i], "()"))
	{
		joined = char_join(str[(*i)++], '\0', '\0', '\0');
		if (!joined)
			custom_exit(d, "alloc of split token failed", NULL, EXIT_FAILURE);
	}
	return (joined);
}

char	*get_new_split(t_data *d, char *str, int *i)
{
	char	*new_split;
	int		len;
	int		size;

	new_split = get_token_in_split(d, str, i);
	if (new_split)
		return (new_split);
	len = *i;
	while (str[len] && (!char_in_str(str[len], "()<>&| ") \
		|| is_in_quote(str, len)))
		len++;
	size = (len - *i + 1);
	new_split = ms_malloc(d, size);
	len = 0;
	while (len < size - 1)
		new_split[len++] = str[(*i)++];
	new_split[len] = '\0';
	return (new_split);
}

char	**split_input(t_data *d, char *input)
{
	char	**splits;
	int		token_index;
	int		i;
	int		input_len;

	token_index = 0;
	input_len = ft_strlen(input);
	splits = ms_malloc(d, sizeof(char *) * (input_len + 1));
	i = 0;
	while (i < input_len && input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (!input[i])
			break ;
		splits[token_index++] = get_new_split(d, input, &i);
	}
	splits[token_index] = NULL;
	return (splits);
}

void	unquote_splits(t_data *d, char **splits)
{
	int	i;

	i = -1;
	while (splits[++i])
		remove_chars(d, &splits[i], "\'\"");
}
