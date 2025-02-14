/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:28:54 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/14 00:25:52 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	handle_direct_exec(t_data *d, char *cmd_name, char *arg, char **flags)
{
	char	**new_flg;
	char	*rm_name;
	int		i;
	int		arr_len;
	int		fct_ret;

	rm_name = ms_strdup(d, cmd_name);
	arr_len = get_arr_len((void **)flags) + 1;
	if (arg)
		arr_len++;
	new_flg = ms_malloc(d, sizeof(char *) * (arr_len + 1));
	new_flg[0] = ms_strdup(d, rm_name);
	new_flg[1] = NULL;
	i = 0;
	if (arg)
	{
		new_flg[1] = ms_strdup(d, arg);
		i = 1;
	}
	while (++i < arr_len)
		new_flg[i] = ms_strdup(d, flags[i - 1 - (arg != NULL)]);
	new_flg[i] = NULL;
	fct_ret = exec(d, rm_name, new_flg, 1);
	free_void_array((void ***)&new_flg);
	return (free(rm_name), fct_ret);
}

//	echo "ola" -n (echo = cmd_name | "ola" = arg | -n = flags)
int	execute_command(t_data *d, char *cmd_name, char *arg, char **flags)
{
	int		i;

	i = -1;
	while (d->bltin_names[++i])
		if (cmp_str(d->bltin_names[i], cmd_name))
			return (d->blt_fct[i](d, arg, flags, EXIT_SUCCESS));
	if (cmp_str(cmd_name, "var") && d->var_list)
		return (dblst_print_list(d->var_list, 0), FCT_SUCCESS);
	else if (chr_amnt(cmd_name, '=') == 1)
		return (export(d, cmd_name, flags, 1));
	else if (cmp_str(cmd_name, "declare") && arg && cmp_str(arg, "-x"))
		return (export(d, flags[0], &flags[1], 0));
	else if (cmp_str(cmd_name, "declare"))
		return (export(d, arg, flags, 1));
	return (handle_direct_exec(d, cmd_name, arg, flags));
}

t_token	*handle_logical_token(t_data *d, t_token *node)
{
	int			min_par;

	if ((cmp_str(node->name, "||") && d->last_exit_st == FCT_SUCCESS) || \
	(cmp_str(node->name, "&&") && d->last_exit_st > 0))
	{
		min_par = node->par;
		node = node->next;
		if (node && node->next)
			node = node->next;
		while (node && (((node->type == tk_argument || node->is_redir) || node->par > min_par)))
		{
			if (d->debug_mode)
				printf("%sskipped %s%s\n", GREY, node->name, RESET);
			node = node->next;
		}
		if (node && node->is_redir)
			return (node->next);
		return (node);
	}
	return (node->next);
}

t_token	*handle_token(t_data *d, t_token *node)
{
	t_tktype	type;

	type = node->type;
	if (type == tk_hered)
	{
		handle_redir_heredoc(d, node->next);
		return (node->next->next);
	}
	if (type == tk_logical)
		return (handle_logical_token(d, node));
	else if (type == tk_command || type == tk_exec)
	{
		if (node->pipe_out)
			return (handle_pipe(d, node));
		return (handle_command_token(d, node, 1));
	}
	if (type == tk_argument && chr_amnt(node->name, '=') == 1)
		export(d, node->name, NULL, 1);
	return (node->next);
}

int	exec_prompt(t_data *d, char *terminal_line)
{
	t_token	*tokens;
	t_token	*node;

	tokens = tokenize_string(d, terminal_line);
	if (!tokens)
		return (FCT_FAIL);
	node = token_first(tokens);
	d->last_cmd_status = -1;
	while (node)
	{
		update_node_expansion(d, node, 1);
		if (!validate_token(d, node))
			break ;
		if (d->debug_mode)
			show_cmd_status(d, node);
		node = handle_token(d, node);
	}
	if (d->heredocfd != -1)
		consumate_heredoc(d, NULL, NULL, NULL);
	tokens = token_first(tokens);
	clear_tokens(tokens);
	return (d->last_cmd_status);
}
