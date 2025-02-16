/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:15:55 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/16 10:29:15 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

t_token	*set_args(t_data *d, t_token *cmd, t_token *arg_token, char ***flags)
{
	t_dblist	*list;
	t_token		*node;
	char		**new_arr;

	list = NULL;
	node = arg_token->next;
	while (node && (node->type == tk_argument || \
		(cmd->redir && cmd->redir == node)))
	{
		if (!node->is_redir && !(cmd->red_arg && cmd->red_arg == node))
		{
			update_node_expansion(d, node, 0);
			dblst_add_back(&list, dblst_new(ms_strdup(d, node->name)));
		}
		node = node->next;
	}
	if (!list)
		return (arg_token);
	list = dblst_first(list);
	new_arr = list_to_arr(list);
	dblst_clear(&list, free);
	free_void_array((void ***)flags);
	*flags = new_arr;
	return (node);
}

t_token	*setup_args(t_data *d, char **arg, t_token *cmd, char ***flags)
{
	t_token	*arg_token;

	if (!cmd->next)
		return (NULL);
	if (cmd->next->type != tk_argument)
		return (cmd->next);
	arg_token = cmd->next;
	update_node_expansion(d, arg_token, 0);
	*arg = arg_token->name;
	if (!arg_token->next)
	{
		*flags = NULL;
		return (NULL);
	}
	return (set_args(d, cmd, arg_token, flags));
}

t_token	*consumate_heredoc(t_data *d, t_token *cmd, char *arg, char **flags)
{
	char	*content;

	d->heredocfd = open(d->heredoc_wd, O_RDONLY, 0644);
	if (!cmd)
	{
		content = get_fd_content(d, d->heredocfd);
		if (content)
			printf("%s", content);
		return (NULL);
	}
	save_stds(d);
	dup2(d->heredocfd, STDIN_FILENO);
	d->last_exit_st = execute_command(d, cmd->name, arg, flags);
	reset_redir(d);
	d->heredocfd = -1;
	close(d->heredocfd);
	if (cmd->red_arg)
		return (cmd->red_arg->next);
	return (cmd->next);
}

int	validate_redir(t_data *d, t_token *redir)
{
	if (d->heredocfd != -1)
		return (1);
	if (!redir->next)
		return (printf("syntax error near \
			unexpected token `newline'\n"), 0);
	else if (redir->type == tk_red_in && access(redir->next->name, F_OK) == -1)
		return (printf("mash: %s: No such file or directory\n", \
			redir->next->name), 0);
	return (1);
}

t_token	*handle_command_token(t_data *d, t_token *node, int should_redir)
{
	t_token		*nxt;
	char		**flags;
	char		*arg;

	arg = NULL;
	flags = NULL;
	nxt = setup_args(d, &arg, node, &flags);
	if ((should_redir && node->redir) || d->heredocfd != -1)
	{
		if (!validate_redir(d, node->redir))
			return (NULL);
		if (node->redir)
			nxt = handle_redir_cmd(d, node, arg, flags);
		if (d->heredocfd != -1)
			nxt = consumate_heredoc(d, node, arg, flags);
	}
	else
		d->last_exit_st = execute_command(d, node->name, arg, flags);
	if (d->debug_mode)
		show_exec_info(d, node, arg, flags);
	if (nxt && nxt->type == tk_argument)
		nxt = nxt->next;
	return (free_void_array((void ***)&flags), nxt);
}
