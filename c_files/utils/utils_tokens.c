/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:29:00 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/30 11:17:58 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	**init_flags(t_data *d, int splits_amount, char **splits)
{
	int		i;
	char	**flags;

	flags = malloc(sizeof(char *) * (splits_amount - 1));
	if (!flags)
	{
		free_void_array((void ***)&splits);
		custom_exit(d, "Alloc failed for flags", NULL, EXIT_FAILURE);
	}
	i = 1;
	while (splits[++i])
	{
		flags[i - 2] = ft_strdup(splits[i]);
		if (!flags[i - 2])
		{
			free_void_array((void ***)&flags);
			free_void_array((void ***)&splits);
			custom_exit(d, "Alloc failed for token", NULL, EXIT_FAILURE);
		}
	}
	flags[i - 2] = NULL;
	return (flags);
}

char	**split_prompt(char *str, int str_len)
{
	char	**tokens;
	int		token_index;
	int		tlen;
	int		i;

	token_index = 0;
	str_len = ft_strlen(str);
	tokens = malloc(sizeof(char *) * str_len);
	i = -1;
	while (i < str_len && str[++i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		tlen = i;
		while (str[tlen] && (is_in_quote(str, tlen) || str[tlen] != ' '))
			tlen++;
		tokens[token_index] = malloc((tlen - i) + 1);
		tlen = 0;
		while (str[i] && (is_in_quote(str, i) || str[i] != ' '))
			tokens[token_index][tlen++] = str[i++];
		tokens[token_index++][tlen] = '\0';
	}
	return (tokens[token_index] = NULL, tokens);
}

char	**get_splits(t_data *d, char *prmpt, char **cmd_name, char **arg)
{
	char	**splits;

	splits = split_prompt(prmpt, ft_strlen(prmpt));
	!splits && (custom_exit(d, "Alloc failed for tokens", NULL, EXIT_FAILURE));
	expand_splits(d, splits);
	*cmd_name = ft_strdup(splits[0]);
	if (!*cmd_name)
	{
		free_void_array((void ***)&splits);
		custom_exit(d, "Alloc failed for arg", NULL, EXIT_FAILURE);
	}
	if (splits[1])
	{
		*arg = ft_strdup(splits[1]);
		if (!*arg)
		{
			free_void_array((void ***)&splits);
			custom_exit(d, "Alloc failed for arg", NULL, EXIT_FAILURE);
		}
	}
	return (splits);
}

char	**get_flags(t_data *d, char *prmpt, char **cmd_name, char **arg)
{
	char	**splits;
	char	**flags;
	int		splits_len;

	splits = get_splits(d, prmpt, cmd_name, arg);
	
	splits_len = get_arr_len((void **)splits);
	if (splits_len - 1 <= 0)
		return (NULL);
	flags = init_flags(d, splits_len, splits);
	free_void_array((void ***)&splits);
	return (flags);
}
