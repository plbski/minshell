/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:56:26 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/31 09:07:31 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

t_toktype	get_token_type_2(t_data *d, char *str, t_token *prev)
{
	(void)d;
	if (ch_amount(str, '\''))
		return (tk_quote);
	if (ch_amount(str, '\"'))
		return (tk_dbquote);
	if (is_same_string(str, "*"))
		return (tk_wildcard);
	if (is_same_string(str, "..") || is_same_string(str, "."))
		return (tk_argument);
	if (!prev || (prev->type != tk_exec && prev->type != tk_command))
	{
		if (str[0] == '.' && str[1] == '/')
			return (tk_exec);
		if (access(str, X_OK) != -1)
			return (tk_exec);
	}
	return (tk_argument);
}

t_toktype	get_token_type(t_data *d, char *str, t_token *prev)
{
	int	i;

	if (prev && (prev->type == tk_redir_out || prev->type == tk_redir_app))
		return (tk_argument);
	if (!prev || prev->type == tk_pipe || prev->type == tk_logical || prev->type == tk_argument)
	{
		i = -1;
		while (d->bltin_names[++i])
			if (is_same_string(str, d->bltin_names[i]))
				return (tk_command);
	}
	if (is_same_string(str, "<"))
		return (tk_redir_in);
	if (is_same_string(str, ">"))
		return (tk_redir_out);
	if (is_same_string(str, ">>"))
		return (tk_redir_app);
	if (is_same_string(str, "<<"))
		return (tk_heredox);
	if (is_same_string(str, "|"))
		return (tk_pipe);
	if (is_same_string(str, "&&") || is_same_string(str, "||"))
		return (tk_logical);
	return (get_token_type_2(d, str, prev));
}

const char *types_names[] = {"command", "argument", "expand arg", "in", "out", "append", "heredoc", "pipe", "logical", "quote", "dbqupte", "wildcard", "flags", "exec"};

int	validate_tokens(t_token *node)
{
	t_toktype	type;
	int			has_command;

	has_command = 0;
	while (node)
	{
		type = node->type;
		if (type != tk_command && type != tk_exec && type != tk_heredox && !has_command)
		{
			printf("msh: command not found: %s\n", node->name);
			return (0);
		}
		if (type == tk_command || type == tk_exec || type == tk_heredox)
			has_command = 1;
		if ((type == tk_redir_out || type == tk_redir_app) && !node->next)
		{
			printf("msh: parse error near \'%s\'\n", node->name);
			return (0);
		}
		node = node->next;
	}
	return (1);
}

t_token	*tokenize_string(t_data *d, char *prompt)
{
	char		**splits;
	t_token		*token;
	t_token		*node;
	t_toktype	type;
	int			i;

	splits = split_prompt(prompt, ' ');
	expand_splits(d, splits);
	token = NULL;
	i = -1;
	while (splits[++i])
	{
		type = get_token_type(d, splits[i], token);
		token = new_token(splits[i], token, type);
	}
	node = token_first(token);
	if (!validate_tokens(node))
		return (clear_tokens(token), NULL);
	return (token);
}
