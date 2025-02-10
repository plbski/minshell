/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:29:00 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/10 11:04:16 by giuliovalen      ###   ########.fr       */
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

void	unquote_splits(t_data *d, char **splits)
{
	int	i;

	i = -1;
	while (splits[++i])
		remove_chars(d, &splits[i], "\'\"");
}

t_token	*get_next_token(t_token *token, t_tktype type, int stops_at_same)
{
	t_tktype	same_type;

	same_type = token->type;
	token = token->next;
	while (token)
	{
		if (token->type == type)
			return (token);
		if (stops_at_same && token->type == same_type)
			return (NULL);
		token = token->next;
	}
	return (NULL);
}

void	link_token_pipes(t_token *tokens)
{
	t_token	*node;
	t_token	*output;

	node = token_first(tokens);
	while (node)
	{
		if (node->type == tk_command || node->type == tk_exec)
		{
			output = get_next_token(node, tk_pipe, 1);
			if (output)
			{
				node->pipe_out = output->next;
				if (output->next->type != tk_command)
					output->next->type = tk_exec;
			}
		}
		node = node->next;
	}
}
