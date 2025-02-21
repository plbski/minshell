/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_execute_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:15:55 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/21 18:46:42 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static t_token	*set_args(t_data *d, t_token *cmd, t_token *arg_token, char ***flags)
{
	t_dblist	*list;
	t_token		*node;
	char		**new_arr;

	list = NULL;
	node = arg_token->next;
	while (node && (node->type == tk_arg || (cmd->redir && cmd->redir == node)))
	{
		if (!node->is_rd && (!cmd->red_arg || cmd->red_arg != node))
		{
			update_node_expansion(d, node);
			if (!node->name)
				node->name = ms_strdup(d, "");
			dblst_add_back(&list, dblst_new(ms_strdup(d, node->name)));
		}
		node = node->next;
	}
	if (!list)
		return (arg_token);
	list = dblst_first(list);
	new_arr = dblst_to_arr(list);
	dblst_clear(&list, free);
	free_void_array((void ***)flags);
	*flags = new_arr;
	return (node);
}

t_token	*setup_args(t_data *d, char **arg, t_token *cmd, char ***flags)
{
	t_token	*arg_token;

	arg_token = cmd->next;
	if (arg_token && arg_token->is_rd)
		arg_token = arg_token->next->next;
	if (!arg_token)
		return (NULL);
	if (arg_token->type != tk_arg)
		return (arg_token);
	update_node_expansion(d, arg_token);
	*arg = arg_token->name;
	if (!*arg)
		*arg = ft_strdup("");
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
	d->last_exit = execute_command(d, cmd->name, arg, flags);
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
		return (ft_dprintf(2, "msh: %s: No such file or directory\n", \
			redir->next->name), 0);
	return (1);
}

void	swap_redir_cmd(t_data *d, t_token *node)
{
	t_token	*red_arg;
	t_token	*cmd;

	red_arg = node->next;
	red_arg->type = tk_arg;
	cmd = red_arg->next;
	if (!cmd || ((((cmd->type == tk_cmd || cmd->type == tk_arg) && \
		(cmd->next && cmd->next->is_rd)))))
	{
		cmd = new_token(ms_strdup(d, "null"), node->prv, tk_cmd, node->par);
		if (node->prv)
			node->prv->next = cmd;
		node->prv = cmd;
		cmd->next = node;
	}
	else
	{
		swap_tokens(node, cmd);
		swap_tokens(cmd, red_arg);
		cmd = node;
	}
	cmd->type = tk_cmd;
}
