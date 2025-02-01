/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:05:09 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/01 02:08:45 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

//	iterate until !ok_type, fill list with args, returns pointer to last arg + 1
t_token	*set_args(t_data *d, t_token *strt, t_toktype k_typ, char ***args)
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
	new_args = malloc(sizeof(char *) * (flags_amount + 1));
	next_node = strt->next;
	arg_index = 0;
	while (next_node && next_node->type == k_typ)
	{
		update_node_expansion(d, next_node, 0);
		new_args[arg_index++] = next_node->name;
		next_node = next_node->next;
	}
	new_args[arg_index] = NULL;
	*args = new_args;
	return (next_node);
}

void	close_redir_stream(t_data *d)
{
	if (dup2(1, STDOUT_FILENO) == -1)
		custom_exit(d, "erreur dup2", NULL, EXIT_FAILURE);
	if (dup2(0, STDOUT_FILENO) == -1)
		custom_exit(d, "erreur dup2", NULL, EXIT_FAILURE);
	if (d->fd)
		close(d->fd);
	d->fd = 0;
}

t_token	*execute_cmd_token(t_data *d, t_token *node)
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
	if (redir)
		nxt = handle_redir(d, nxt, nxt->type);
	d->last_exit_status = execute_command(d, node->name, arg, flags);
	if (redir)
		close_redir_stream(d);
	if (d->debug_mode)
		show_exec_info(node, arg, flags, d->last_exit_status);
	return (nxt);
}

t_token	*execute_token(t_data *d, t_token *node)
{
	t_toktype	type;
	int			min_par;

	type = node->type;
	if (type == tk_command || type == tk_exec)
		return (execute_cmd_token(d, node));
	if (type == tk_hered)
		return (handle_redir(d, node, node->type));
	if (type == tk_argument && chr_amnt(node->name, '=') == 1)
		export(d, node->name, NULL, 1);
	if (cmp_str(node->name, "||") && d->last_exit_status == FCT_SUCCESS)
	{
		if (d->debug_mode)
			printf("%sskipped %s%s\n", GREY, node->name, RESET);
		node = node->next;
	}
	if (cmp_str(node->name, "&&") && d->last_exit_status == FCT_FAIL)
	{
		min_par = node->par;
		while (node->next && node->next->par >= min_par)
		{
			if (d->debug_mode)
				printf("%sskipped %s%s\n", GREY, node->name, RESET);
			node = node->next;
		}
	}
	return (node->next);
}

int	exec_prompt(t_data *d, char *terminal_line)
{
	t_token	*tokens;
	t_token	*node;
	int		cur_par;

	tokens = tokenize_string(d, terminal_line);
	if (!tokens)
		return (FCT_FAIL);
	node = token_first(tokens);
	d->last_cmd_status = -1;
	cur_par = 1;
	(void)cur_par;
	while (node)
	{
		update_node_expansion(d, node, 1);
		if (!validate_token(node))
			break ;
		if (d->debug_mode)
		{
			printf("(st: %s) ", d->last_exit_status == FCT_FAIL ? "\033[31mFAIL" : "\033[32mSUCCESS");
			printf("%s", RESET);
			show_token_info(node, "evaluating", "\n");
		}
		close_redir_stream(d);
		node = execute_token(d, node);
	}
	clear_tokens(tokens);
	return (d->last_cmd_status);
}
