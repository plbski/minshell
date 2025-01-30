/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:33:06 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/30 12:35:09 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"
#include "../../libft/libft.h"

t_token	*new_token(char *content, t_token *prv, t_token_typ type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->next = NULL;
	if (prv)
	{
		prv->next = token;		
		token->prv = prv;
	}
	token->content = content;
	token->type = type;
	return (token);
}

t_token	*token_first(t_token *lst)
{
	t_token	*first;

	first = lst;
	while (first->prv)
		first = first->prv;
	return (first);
}

t_token	*get_token(t_token *lst, char *content)
{
	t_token	*first;

	first = token_first(lst);
	if (!first)
		return (NULL);
	while (first->next)
	{
		if (is_same_string(first->content, content))
			return (first);
		first = first->next;
	}
	return (NULL);
}

int	token_clear(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return (0);
	token = token_first(token);
	while (token)
	{
		tmp = token;
		if (tmp->content)
			free(tmp->content);
		token = token->next;
		free(tmp);
	}
	return (1);
}

t_token_typ get_token_type(t_data *d, char *str)
{
	int i;

	i = -1;
	while (d->bltin_names[++i])
		if (is_same_string(str, d->bltin_names[i]))
			return (tk_command);
	if (is_same_string(str, "<<"))
		return (tk_heredox);
	if (is_same_string(str, ">>"))
		return (tk_redir_append);
	if (is_same_string(str, ">"))
		return (tk_redir_out);
	if (is_same_string(str, "<"))
		return (tk_redir_in);
	if (is_same_string(str, "|"))
		return (tk_pipe);
	if (is_same_string(str, "&&") || is_same_string(str, "||"))
		return (tk_logical);
	if (ch_amount(str, '\''))
		return (tk_quote);
	if (ch_amount(str, '\"'))
		return (tk_dbquote);
	if (is_same_string(str, "*"))
		return (tk_wildcard);
	if (ch_amount(str, '$'))
		return (tk_expand_arg);
	return (tk_argument);
}

const char *types_names[] = {"command", "argument", "expand arg", "in", "out", "append", "heredoc", "pipe", "logical", "quote", "dbqupte", "wildcard"};

t_token *get_tokens_from_splits(t_data *d, char *prompt)
{
	char		**splits;
	t_token		*token;
	t_token		*node;
	int			i;

	splits = split_prompt(prompt, ' ');
	token = NULL;
	i = -1;
	while (splits[++i])
		token = new_token(splits[i], token, get_token_type(d, splits[i]));
	node = token_first(token);
	while (node->next)
	{
		node = node->next;
		printf("%s : %s\n", node->content, types_names[node->type]);
	}
	return (token);
}
