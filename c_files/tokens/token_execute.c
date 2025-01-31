/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:05:09 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/31 01:06:25 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

//	iterate until !ok_type, fill list with args, returns pointer to last arg + 1
t_token	*set_token_args(t_token *start_node, t_toktype ok_type, char ***args)
{
	char		**new_args;
	int			arg_index;
	t_token		*next_node;
	int			flags_amount;

	flags_amount = 0;
	next_node = start_node->next;
	while (next_node && next_node->type == ok_type)
	{
		flags_amount++;
		next_node = next_node->next;
	}
	new_args = malloc(sizeof(char *) * (flags_amount + 1));
	next_node = start_node->next;
	arg_index = 0;
	while (next_node && next_node->type == ok_type)
	{
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

t_token	*execute_cmd_token(t_data *d, t_token *node, int *fct_ret)
{
	t_token		*nxt;
	char		*arg_0;
	char		**flags;
	int			has_redir;

	flags = NULL;
	arg_0 = NULL;
	nxt = node->next;
	if (nxt && nxt->type == tk_argument)
	{
		arg_0 = nxt->name;
		nxt = set_token_args(nxt, tk_argument, &flags);
	}
	has_redir = (nxt && (nxt->type == tk_redir_app || nxt->type == tk_redir_in || \
		nxt->type == tk_redir_out || nxt->type == tk_heredox));
	if (has_redir)
		nxt = handle_redir(d, nxt, nxt->type);
	*fct_ret = execute_command(d, node->name, arg_0, flags);
	if (has_redir)
		close_redir_stream(d);
	if (!fct_ret)
		return (NULL);
	return (nxt);
}

t_token	*execute_token(t_data *d, t_token *node, int *fct_return)
{
	t_toktype	type;

	type = node->type;
	if (type == tk_command || type == tk_exec)
		return (execute_cmd_token(d, node, fct_return));
	if (type == tk_heredox)
		return (handle_redir(d, node, node->type));
	return (node->next);
}

int	exec_prompt(t_data *d, char *terminal_line)
{
	t_token	*tokens;
	t_token	*node;
	int		fct_ret;

	fct_ret = 1;
	tokens = tokenize_string(d, terminal_line);
	if (!tokens)
		return (FCT_FAIL);
	node = token_first(tokens);
	while (node)
		node = execute_token(d, node, &fct_ret);
	clear_tokens(tokens);
	return (fct_ret);
}
