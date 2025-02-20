/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:33:16 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/14 03:56:49 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static char	*get_quote_end(t_data *d, char *end, char *msg)
{
	char	*quote_append;
	char	*quote_end;

	quote_append = parse_heredoc(end, d, msg);
	if (!quote_append)
		return (NULL);
	quote_end = ms_strjoin(d, quote_append, end);
	free(quote_append);
	return (quote_end);
}

static int	set_quotes(t_data *d, char **input)
{
	char	*quote_end;
	int		qt_index;
	int		dbqt_index;
	char	*new_input;

	qt_index = -1;
	dbqt_index = -1;
	quote_end = NULL;
	if (chr_amnt(*input, '\'') % 2 == 1)
		qt_index = get_char_index(*input, '\'');
	if (chr_amnt(*input, '\"') % 2 == 1)
		dbqt_index = get_char_index(*input, '\"');
	if ((qt_index == -1 || in_quote(*input, qt_index)) && \
		(dbqt_index == -1 || in_quote(*input, dbqt_index)))
		return (1);
	if ((qt_index > 0 && qt_index < dbqt_index) || dbqt_index == -1)
		quote_end = get_quote_end(d, "\'", "quote> ");
	else
		quote_end = get_quote_end(d, "\"", "dquote> ");
	if (!quote_end)
		return (0);
	new_input = ms_strjoin(d, *input, quote_end);
	free(quote_end);
	return (free(*input), *input = new_input, 1);
}

static int	set_par(t_data *d, char **input, int i)
{
	int		has_open;
	char	*input_end;
	char	*new_input;

	new_input = *input;
	has_open = 0;
	while (new_input[++i])
	{
		if (new_input[i] == '(')
			has_open++;
		if (new_input[i] != ')')
			continue ;
		if (!has_open)
			return (printf("syntax error near unexpected token `)'\n"), 0);
		has_open--;
	}
	if (!has_open)
		return (1);
	input_end = get_quote_end(d, ")", "> ");
	if (!input_end)
		return (0);
	new_input = ms_strjoin(d, *input, input_end);
	return (free(input_end), free(*input), *input = new_input, 1);
}

static int	find_unvalid_patterns(char *input)
{
	const char	patterns[13][4] = {"| |", "& &", "& |", "| &", \
		"&|", "|&", ">|", "<|", "|>", "|<", "< <", "$)", "> >"};
	char		*pattern;
	int			i;

	i = -1;
	while (++i < 13)
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

int	validate_input(t_data *d, char **input)
{
	int		i;
	int		has_redir;
	char	*str;

	if (!*input || *input[0] == '\0' || find_unvalid_patterns(*input))
		return (0);
	if (!set_quotes(d, input) || !set_par(d, input, -1) || !set_pipe(d, input))
		return (0);
	has_redir = 0;
	str = *input;
	i = -1;
	while (str[++i])
	{
		if ((str[i] == ';' || str[i] == '\\') && !in_quote(str, i))
			return (ft_dprintf(2, "msh: syntax error near \
unexpected token `%c'\n", str[i]), 0);
		if ((str[i] == '<' || str[i] == '>') && !in_quote(str, i))
			has_redir = 1;
	}
	if (!has_redir)
		return (1);
	return (check_redir_validity(*input));
}
