/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_checker2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:33:49 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/13 19:05:18 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

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

static int	check_pipe_validity(t_data *d, char **prmpt, int last_pipe_index)
{
	int		i;
	char	*heredoc_content;
	char	*new_prmpt;
	char	*str;

	if (last_pipe_index == -1)
		return (1);
	str = *prmpt;
	i = last_pipe_index + 1;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
	{
		heredoc_content = parse_heredoc(NULL, d, "> ");
		if (!heredoc_content)
			return (0);
		new_prmpt = ms_strjoin(d, *prmpt, heredoc_content);
		free(*prmpt);
		*prmpt = new_prmpt;
	}
	return (1);
}

int	set_pipe(t_data *d, char **prmpt)
{
	char	*str;
	int		pipe_index;
	int		i;
	int		no_space_found;

	no_space_found = 0;
	pipe_index = -1;
	i = -1;
	str = *prmpt;
	while (str[++i])
	{
		if (char_in_str(str[i], "|&") && !is_in_quote(str, i))
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
	return (check_pipe_validity(d, prmpt, pipe_index));
}

static char	is_valid_redir(char *p, int i, int j, char c)
{
	if (char_in_str(p[0], "&|>"))
		return (p[0]);
	while (p[++i])
	{
		c = p[i];
		if (char_in_str(p[i], "><"))
		{
			j = i + 1;
			while (p[j] == ' ')
				j++;
			if ((p[i] == '>' && p[j] == '<') || (p[i] == '<' && p[j] == '>'))
				return (c);
			j = 0;
			while (p[i + j] && (p[i + j] == '>' || p[i + j] == '<'))
				j++;
			if (j >= 3)
				return (c);
			i += j - 1;
			while (p[++i] == ' ')
				continue ;
			if (!p[i])
				return (c);
		}
	}
	return ('\0');
}

int	check_redir_validity(char *prompt)
{
	char	invalid_token;

	invalid_token = is_valid_redir(prompt, -1, 0, 0);
	if (invalid_token)
	{
		ft_dprintf(2, "msh: syntax error near \
unexpected token %c\n", invalid_token);
		return (0);
	}
	return (1);
}
