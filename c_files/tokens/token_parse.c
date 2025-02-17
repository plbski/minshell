/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:56:26 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/17 18:10:18 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

t_tktype	get_token_type(t_token *prv_eval, char *str)
{
	if (same_str(str, "<"))
		return (tk_red_in);
	if (same_str(str, ">"))
		return (tk_red_out);
	if (same_str(str, ">>"))
		return (tk_red_app);
	if (same_str(str, "<<"))
		return (tk_hered);
	if (same_str(str, "|"))
		return (tk_pipe);
	if (same_str(str, "&&") || same_str(str, "||"))
		return (tk_logical);
	if (same_str(str, "*"))
		return (tk_wildcard);
	if (prv_eval && prv_eval->type == tk_command)
		return (tk_argument);
	return (tk_command);
}

static t_token	*fill_wildcard(t_data *d, t_token *start, int brk)
{
	DIR				*directory;
	struct dirent	*entry;
	char			*arg_name;

	directory = get_directory(d, d->cwd);
	if (!directory)
		custom_exit(d, "no dir for wildcard", NULL, EXIT_FAILURE);
	entry = readdir(directory);
	while (entry)
	{
		arg_name = ms_strdup(d, entry->d_name);
		if (arg_name[0] != '.')
			start = new_token(ms_strdup(d, arg_name), start, tk_argument, brk);
		free(arg_name);
		entry = readdir(directory);
	}
	closedir(directory);
	return (start);
}

static	t_token	*set_tok(t_data *d, t_token *prv, char *splt, t_token *prv_eval)
{
	t_tktype	type;
	t_token		*new_tok;

	type = get_token_type(prv_eval, splt);
	if (type == tk_wildcard)
		new_tok = fill_wildcard(d, prv, d->brackets);
	else
		new_tok = new_token(ms_strdup(d, splt), prv, type, d->brackets);
	return (new_tok);
}

static t_token	*get_split_tokens(t_data *d, char **splits)
{
	t_token		*list;
	t_token		*prv_eval;
	int			i;

	list = NULL;
	prv_eval = NULL;
	d->brackets = 0;
	i = -1;
	while (splits[++i])
	{
		if (same_str(splits[i], "(") || same_str(splits[i], ")"))
		{
			d->brackets += 2 * (splits[i][0] == '(') - 1;
			continue ;
		}
		list = set_tok(d, list, splits[i], prv_eval);
		if (list->type == tk_command || list->type == tk_pipe || list->type == tk_logical)
		{
			if (prv_eval)
				prv_eval->nxt_eval = list;
			prv_eval = list;
		}
		else if (list->type && prv_eval && prv_eval->type == tk_command)
			prv_eval->redir = list;
	}
	return (list);
}

t_token	*get_next_redir(t_token *d)
{
	t_token	*node;

	if (!d)
		return (NULL);
	node = d->next;
	while (node)
	{
		if (node->type != tk_argument)
			break ;
		node = node->next;
	}
	if (node && node->is_redir)
		return (node);
	while (node && node->par >= d->par)
		node = node->next;
	if (node && node->is_redir)
		return (node);
	return (NULL);
}

void	set_redir_args(t_token *tok)
{
	while (tok)
	{
		if (tok->type == tk_command)
		{
			tok->redir = get_next_redir(tok);
			if (tok->redir && tok->redir->type != tk_red_in)
				tok->red_arg = tok->redir->next;
			else if (tok->redir)
				tok->red_arg = get_last_arg(tok);
		}
		tok = tok->next;
	}
}

t_token	*tokenize_string(t_data *d, char *prompt)
{
	char		**splits;
	t_token		*token;

	splits = split_input(d, prompt);
	token = get_split_tokens(d, splits);
	free_void_array((void ***)&splits);
	token = token_first(token);
	link_token_pipes(token);
	set_redir_args(token);
	if (d->debug_mode)
		show_tokens_info(d, token, "init", "");
	return (token);
}
