/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:56:26 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/03/04 12:39:04 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

t_tktype	get_token_type(t_token *prv_eval, t_token *prv, char *str)
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
	if (same_str(str, ";"))
		return (tk_cmdsep);
	if (same_str(str, "&&") || same_str(str, "||"))
		return (tk_logical);
	if (chr_amnt(str, '*', 1))
		return (tk_wildcard);
	if (prv && prv->is_rd)
		return (tk_arg);
	if (prv_eval && prv_eval->type == tk_cmd)
		return (tk_arg);
	return (tk_cmd);
}

static	t_token	*set_tok(t_data *d, t_token *prv, char **sp, t_token *prv_evl)
{
	t_tktype	type;
	t_token		*new_tok;
	int			rd_fd;
	char		nbr_buffer[999];
	int			i;

	rd_fd = -1;
	i = -1;
	while (ft_isdigit((*sp)[++i]))
		nbr_buffer[i] = (*sp)[i];
	nbr_buffer[i] = '\0';
	if (i > 0 && (only_chars((*sp) + i, ">") || only_chars((*sp) + i, "<" )))
	{
		rd_fd = ft_atoi(nbr_buffer);
		ms_rem_prefix(d, sp, nbr_buffer, 0);
	}
	type = get_token_type(prv_evl, prv, *sp);
	if (type == tk_wildcard)
		new_tok = fill_wildcard(d, prv, *sp, d->brackets);
	else
		new_tok = new_token(*sp, prv, type, d->brackets);
	if (rd_fd < 3)
		new_tok->rd_fd = rd_fd;
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
		lst = set_tok(d, lst, &splits[i], prv_eval);
		if (lst->type != tk_arg && lst->type != tk_cmdsep && !lst->is_rd)
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
	set_redir_redir(token);
	if (!set_heredocs(d, token))
		return (clear_tokens(token), NULL);
	link_token_pipes(token);
	set_subshells(d, token);
	if (!validate_token_sequence(d, token))
		return (clear_tokens(token), NULL);
	if (d->debug_mode)
		show_tokens_info(d, token, "Init", -1);
	return (token);
}
