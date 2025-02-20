/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:56:26 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/21 00:47:47 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

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
	if (prv_eval && prv_eval->type == tk_cmd)
		return (tk_arg);
	return (tk_cmd);
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
			start = new_token(ms_strdup(d, arg_name), start, tk_arg, brk);
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

static t_token	*get_split_tokens(t_data *d, char **splits, t_token *lst)
{
	t_token		*prv_eval;
	int			i;

	lst = NULL;
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
		lst = set_tok(d, lst, splits[i], prv_eval);
		if (lst->type != tk_arg && !lst->is_redir)
		{
			if (prv_eval)
				prv_eval->nxt_eval = lst;
			prv_eval = lst;
		}
		else if (lst->type && prv_eval && prv_eval->type == tk_cmd)
			prv_eval->redir = lst;
	}
	return (lst);
}

t_token	*tokenize_string(t_data *d, char *prompt)
{
	char		**splits;
	t_token		*token;

	splits = split_input(d, prompt);
	token = get_split_tokens(d, splits, NULL);
	free_void_array((void ***)&splits);
	token = token_first(token);
	link_token_pipes(token);
	set_redir_args(token);
	set_subshells(d, token);
	if (d->debug_mode)
		show_tokens_info(d, token, "Init", -1);
	return (token);
}
