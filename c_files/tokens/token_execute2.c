/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_execute2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:15:55 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/12 18:28:40 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

//	iterate until !ok_type, fill list with args, returns pointer to last arg + 1
t_token	*set_args(t_data *d, t_token *strt, t_tktype k_typ, char ***args_arr)
{
	t_dblist	*list;
	t_dblist	*node;
	t_token		*next;
	char		**new_arr;

	*args_arr = NULL;
	list = NULL;
	next = strt->next;
	while (next && (next->type == k_typ || next->type == tk_hered))
	{
		if (next->type != tk_hered)
		{
			update_node_expansion(d, next, 0);
			node = dblst_new(ms_strdup(d, next->name));
			dblst_add_back(&list, node);
		}
		next = next->next;
	}
	if (!list)
		return (next);
	list = dblst_first(list);
	new_arr = list_to_arr(list);
	dblst_clear(&list, free);
	*args_arr = new_arr;
	return (next);
}


t_token	*setup_args(t_data *d, char **arg, t_token *nxt, char ***flags)
{
	if (!nxt || nxt->type != tk_argument)
		return (nxt);
	update_node_expansion(d, nxt, 0);
	*arg = nxt->name;
	return (set_args(d, nxt, tk_argument, flags));
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

int	setup_redir_exec(t_data *d, t_token **nxt)
{
	t_token	*redir;

	redir = *nxt;
	if (!redir || (redir->type != tk_red_app && redir->type != tk_red_in \
		&& redir->type != tk_red_out && redir->type != tk_hered))
		return (-1);
	if (!validate_redir(redir))
		return (0);
	if (redir->type == tk_red_app || redir->type == tk_red_out)
		return (redir->type);
	*nxt = handle_redir(d, *nxt, redir->next, redir->type);
	return (redir->type);
}

t_token	*handle_command_token(t_data *d, t_token *node, int handle_redir)
{
	t_token		*nxt;
	char		**flags;
	int			redir;
	char		*arg;

	flags = NULL;
	arg = NULL;
	nxt = setup_args(d, &arg, node->next, &flags);
	redir = -1;
	if (handle_redir)
	{
		redir = setup_redir_exec(d, &nxt);
		if (!redir)
			return (free_void_array((void ***)&flags), NULL);
		if (redir == tk_red_out || redir == tk_red_app)
			nxt = exec_cmd_with_redir(d, node, arg, flags);
		else
			d->last_exit_st = execute_command(d, node->name, arg, flags);
		if (redir != -1)
			close_redir_stream(d);
	}
	else
		d->last_exit_st = execute_command(d, node->name, arg, flags);
	if (d->debug_mode)
		show_exec_info(d, node, arg, flags);
	return (free_void_array((void ***)&flags), nxt);
}
