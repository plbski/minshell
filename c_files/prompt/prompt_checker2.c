/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_checker2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:33:49 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/04 17:39:09 by giuliovalen      ###   ########.fr       */
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
		ft_dprintf(2, "msh: syntax error near unexpected token %c\n", invalid_token);
		return (0);
	}
	return (1);
}

int	check_pipe_validity(t_data *d, char **prmpt, int last_pipe_index)
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
		heredoc_content = heredoc(NULL, d, "> ", 0);
		if (!heredoc_content)
			return (0);
		new_prmpt = ms_strjoin(d, *prmpt, heredoc_content);
		free(*prmpt);
		*prmpt = new_prmpt;
	}
	return (1);
}

int	validate_prmpt_b(char **prmpt, int has_redir, int is_only_spc)
{
	if (is_only_spc)
		return (0);
	if (!has_redir)
		return (1);
	return (check_redir_validity(*prmpt));
}
