/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:33:16 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/31 18:52:51 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	*get_quote_end(t_data *d, char *end, char *msg)
{
	char	*quote_append;
	char	*quote_end;

	quote_append = heredoc(end, d, msg, 1);
	if (!quote_append)
		return (NULL);
	quote_end = ms_strjoin(d, quote_append, end);
	free(quote_append);
	return (quote_end);
}

int	set_quotes(t_data *d, char **prompt)
{
	char	*quote_end;
	int		qt_index;
	int		dbqt_index;
	char	*new_prompt;

	qt_index = -1;
	dbqt_index = -1;
	quote_end = NULL;
	if (chr_amnt(*prompt, '\'') % 2 == 1)
		qt_index = get_char_index(*prompt, '\'');
	if (chr_amnt(*prompt, '\"') % 2 == 1)
		dbqt_index = get_char_index(*prompt, '\"');
	if (qt_index == -1 && dbqt_index == -1)
		return (1);
	if ((qt_index > 0 && qt_index < dbqt_index) || dbqt_index == -1)
		quote_end = get_quote_end(d, "\'", "quote> ");
	else
		quote_end = get_quote_end(d, "\"", "dquote> ");
	if (!quote_end)
		return (0);
	new_prompt = ms_strjoin(d, *prompt, quote_end);
	free(quote_end);
	return (free(*prompt), *prompt = new_prompt, 1);
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
		if (ft_char_in_str(str[i], "|&") && !is_in_quote(str, i))
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

int	set_par(t_data *d, char **prmpt, int i)
{
	int		has_open;
	char	*prmpt_end;
	char	*new_prmpt;

	new_prmpt = *prmpt;
	has_open = 0;
	while (new_prmpt[++i])
	{
		if (new_prmpt[i] == '(')
			has_open = 1;
		if (new_prmpt[i] != ')')
			continue ;
		if (!has_open)
			return (printf("syntax error near unexpected token \')\'\n"), 0);
		has_open = 0;
	}
	if (!has_open)
		return (1);
	prmpt_end = get_quote_end(d, ")", "> ");
	if (!prmpt_end)
		return (0);
	new_prmpt = ms_strjoin(d, *prmpt, prmpt_end);
	return (free(prmpt_end), free(*prmpt), *prmpt = new_prmpt, 1);
}

int	validate_prmpt(t_data *d, char **prmpt)
{
	int		i;
	int		is_only_space;
	int		has_redir;
	char	*str;

	if (!*prmpt || *prmpt[0] == '\0')
		return (0);
	if (!set_quotes(d, prmpt) || !set_par(d, prmpt, -1) || !set_pipe(d, prmpt))
		return (0);
	has_redir = 0;
	str = *prmpt;
	is_only_space = 1;
	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ')
			is_only_space = 0;
		if ((str[i] == '<' || str[i] == '>') && !is_in_quote(str, i))
			has_redir = 1;
	}
	return (validate_prmpt_b(prmpt, has_redir, is_only_space));
}
