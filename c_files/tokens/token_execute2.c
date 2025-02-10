/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_execute2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:15:55 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/10 12:28:28 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

//	iterate until !ok_type, fill list with args, returns pointer to last arg + 1
t_token	*set_args(t_data *d, t_token *strt, t_tktype k_typ, char ***args)
{
	char		**new_args;
	int			arg_index;
	t_token		*next_node;
	int			flags_amount;

	flags_amount = 0;
	next_node = strt->next;
	while (next_node && next_node->type == k_typ)
	{
		flags_amount++;
		next_node = next_node->next;
	}
	new_args = ms_malloc(d, sizeof(char *) * (flags_amount + 1));
	next_node = strt->next;
	arg_index = 0;
	while (next_node && next_node->type == k_typ)
	{
		update_node_expansion(d, next_node, 0);
		new_args[arg_index++] = ms_strdup(d, next_node->name);
		next_node = next_node->next;
	}
	new_args[arg_index] = NULL;
	*args = new_args;
	return (next_node);
}

int	validate_redir(t_token *redir)
{
	if (redir->type == tk_red_in)
	{
		if (!redir->next)
			return (printf("syntax error near \
				unexpected token `newline'\n"), 0);
		else if (access(redir->next->name, F_OK) == -1)
			return (printf("mash: %s: No such file or directory\n", \
				redir->next->name), 0);
	}
	return (1);
}

t_token	*handle_command_token(t_data *d, t_token *node, int handle_redir)
{
	t_token		*nxt;
	char		**flags;
	int			redir;
	char		*arg;

	flags = NULL;
	arg = NULL;
	nxt = node->next;
	if (nxt && nxt->type == tk_argument)
	{
		update_node_expansion(d, nxt, 0);
		arg = nxt->name;
		nxt = set_args(d, nxt, tk_argument, &flags);
	}
	redir = (nxt && (nxt->type == tk_red_app || nxt->type == tk_red_in \
		|| nxt->type == tk_red_out || nxt->type == tk_hered));
	if (redir && handle_redir)
	{
		if (!validate_redir(node->next))
		{
			free_void_array((void ***)&flags);
			return (NULL);
		}
		nxt = handle_redir_token(d, nxt, nxt->type);
	}
	d->last_exit_status = execute_command(d, node->name, arg, flags);
	if (redir && handle_redir)
		close_redir_stream(d);
	if (d->debug_mode)
		show_exec_info(d, node, arg, flags);
	free_void_array((void ***)&flags);
	return (nxt);
}
