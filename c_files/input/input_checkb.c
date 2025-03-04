/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:33:49 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/14 03:57:26 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

int	only_space(char *str)
{
	int	i;
	int	is_only_space;

	is_only_space = 1;
	i = -1;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\t')
			is_only_space = 0;
	return (is_only_space);
}

static int	check_pipe_validity(t_data *d, char **input, int last_pipe_index)
{
	int		i;
	char	*heredoc_content;
	char	*new_input;
	char	*str;

	if (last_pipe_index == -1)
		return (1);
	str = *input;
	i = last_pipe_index + 1;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
	{
		heredoc_content = parse_heredoc(NULL, d, "> ");
		if (!heredoc_content)
			return (0);
		new_input = ms_strjoin(d, *input, heredoc_content);
		free(*input);
		*input = new_input;
	}
	return (1);
}

int	set_pipe(t_data *d, char **input)
{
	char	*str;
	int		pipe_index;
	int		i;
	int		no_space_found;

	no_space_found = 0;
	pipe_index = -1;
	i = -1;
	str = *input;
	while (str[++i])
	{
		if (char_in_str(str[i], "|&") && !in_quote(str, i))
		{
			if (!no_space_found)
			{
				printf("syntax error near unexpected token `%c'\n", str[i]);
				return (0);
			}
			pipe_index = i;
		}
		if (str[i] != ' ')
			no_space_found = 1;
	}
	return (check_pipe_validity(d, input, pipe_index));
}

int	find_unvalid_patterns(char *input)
{
	const char	patterns[12][4] = {"| |", "& &", "& |", "| &", \
		"&|", "|&", ">|", "<|", "|>", "|<", "< <", "> >"};
	char		*pattern;
	int			i;

	i = -1;
	while (++i < 12)
	{
		pattern = ft_strstr(input, patterns[i]);
		if (pattern)
			break ;
	}
	if (pattern)
		return (printf("msh: syntax error near unexpected token `%c'\n", \
				pattern[0]), 1);
	return (0);
}
