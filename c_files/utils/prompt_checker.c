/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:33:16 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/28 22:36:54 by giuliovalen      ###   ########.fr       */
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

int	is_valid_prompt(char *prompt)
{
	int		i;
	int		is_only_space;
	int		has_redir;

	if (!prompt || prompt[0] == '\0')
		return (0);
	has_redir = 0;
	is_only_space = 1;
	i = -1;
	while (prompt[++i])
	{
		if (prompt[i] != ' ')
			is_only_space = 0;
		if ((prompt[i] == '<' || prompt[i] == '>') && !is_in_quote(prompt, i))
			has_redir = 1;
	}
	if (is_only_space)
		return (0);
	if (!has_redir)
		return (1);
	return (check_redir_validity(prompt));
}
