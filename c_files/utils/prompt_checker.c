/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:33:16 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/30 21:40:41 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	is_valid_redir(char *p, int i, int j, char c)
{
	i = -1;
	while (p[++i])
	{
		c = p[i];
		if (p[i] == '>' || p[i] == '<')
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
	return (1);
}

int	check_redir_validity(char *prompt)
{
	char	invalid_token;

	invalid_token = is_valid_redir(prompt, 0, 0, 0);
	if (invalid_token == '>' || invalid_token == '<')
	{
		printf("msh: syntax error near unexpected token %c\n", invalid_token);
		return (0);
	}
	return (1);
}

char	*get_quote_end(t_data *d, char *end, char *msg)
{
	char	*quote_append;
	char	*quote_end;

	quote_append = heredoc(end, d, msg, 1);
	if (!quote_append)
		return (NULL);
	quote_end = ft_strjoin(quote_append, end);
	if (!quote_end)
		custom_exit(d, "error in quote termination", NULL, EXIT_FAILURE);
	free(quote_append);
	return (quote_end);
}

int	handle_quotes(t_data *d, char **prompt)
{
	char	*quote_end;
	int		qt_index;
	int		dbqt_index;
	char	*new_prompt;

	qt_index = -1;
	dbqt_index = -1;
	quote_end = NULL;
	if (ch_amount(*prompt, '\'') % 2 == 1)
		qt_index = get_char_index(*prompt, '\'');
	if (ch_amount(*prompt, '\"') % 2 == 1)
		dbqt_index = get_char_index(*prompt, '\"');
	if (qt_index == -1 && dbqt_index == -1)
		return (1);
	if ((qt_index > 0 && qt_index < dbqt_index) || dbqt_index == -1)
		quote_end = get_quote_end(d, "\'", "quote> ");
	else
		quote_end = get_quote_end(d, "\"", "dquote> ");
	if (!quote_end)
		return (0);
	new_prompt = ft_strjoin(*prompt, quote_end);
	if (!new_prompt)
		custom_exit(d, "alloc for quoted prompt failed", NULL, EXIT_FAILURE);
	free(quote_end);
	return (free(*prompt), *prompt = new_prompt, 1);
}

int	check_pipe_validity(char *prmpt, int last_pipe_index)
{
	int	i;

	if (last_pipe_index == 0)
		return (0);
	i = last_pipe_index + 1;
	if (prmpt[i] != ' ')
		return (0);
	while (prmpt[i] && prmpt[i] == ' ')
		i++;
	if (prmpt[i] == '\0')
		return (0);
	return (1);
}

int	is_valid_prompt(t_data *d, char **prmpt)
{
	int		i;
	int		is_only_space;
	int		has_redir;
	int		pipe_index;
	char	*str;

	str = *prmpt;
	pipe_index = -1;
	if (!str || str[0] == '\0' || !handle_quotes(d, prmpt))
		return (0);
	has_redir = 0;
	is_only_space = 1;
	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ')
			is_only_space = 0;
		if (str[i] == '|' && !is_in_quote(str, i))
			pipe_index = i;
		if ((str[i] == '<' || str[i] == '>') && !is_in_quote(str, i))
			has_redir = 1;
	}
	if (is_only_space)
		return (0);
	if (pipe_index != -1 && !check_pipe_validity(*prmpt, pipe_index))
	{
		printf("syntax error near unexpected token '|\n");
		return (0);
	}
	if (!has_redir)
		return (1);
	return (check_redir_validity(*prmpt));
}
