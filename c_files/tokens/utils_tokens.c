/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:29:00 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/31 23:17:42 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	*get_new_split(char *str, int *i)
{
	char	*new_split;
	int		len;
	int		size;

	if (str[*i] == '(' || str[*i] == ')')
	{
		new_split = malloc(2);
		new_split[0] = str[*i];
		new_split[1] = '\0';
		(*i)++;
		return (new_split);
	}
	len = *i;
	while (str[len] && (is_in_quote(str, len) || !char_in_str(str[len], "() ")))
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
	char	**tokens;
	int		token_index;
	int		i;
	int		str_len;

	token_index = 0;
	str_len = ft_strlen(str);
	tokens = malloc(sizeof(char *) * str_len);
	if (!tokens)
		custom_exit(d, "alloc in split", NULL, EXIT_FAILURE);
	i = 0;
	while (i < str_len && str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		tokens[token_index++] = get_new_split(str, &i);
	}
	return (tokens[token_index] = NULL, tokens);
}

void	unquote_splits(t_data *d, char **splits)
{
	int	i;

	i = -1;
	while (splits[++i])
		remove_chars(d, &splits[i], "\'\"");
}
