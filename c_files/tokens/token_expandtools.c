/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expandtools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:11:49 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/27 12:56:32 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

t_token	*insert_expanded_tokens(t_data *d, t_token *node, char *name)
{
	t_token	*chain_node;
	t_token	*new_chain;

	new_chain = tokenize_string(d, name);
	if (!new_chain)
		return (NULL);
	free(name);
	chain_node = token_first(new_chain);
	chain_node->prv = node;
	while (chain_node->next)
		chain_node = chain_node->next;
	chain_node->next = node->next;
	if (node->next)
		node->next->prv = chain_node;
	node->next = new_chain;
	return (new_chain);
}

t_token	*swap_redir_cmd(t_data *d, t_token *tk)
{
	t_token	*red_arg;
	t_token	*cmd;

	(void)d;
	if (!tk || !tk->is_rd || tk->type == tk_hered || !tk->next)
		return (tk);
	if ((!tk->prv || (tk->prv->type != tk_cmd && tk->prv->type != tk_arg)))
	{
		red_arg = tk->next;
		cmd = new_token("null", tk->prv, tk_cmd, tk->par);
		if (tk->prv)
			tk->prv->next = cmd;
		tk->prv = cmd;
		cmd->next = tk;
		cmd->redir = tk;
		red_arg->type = tk_arg;
		return (cmd);
	}
	return (tk);
}
