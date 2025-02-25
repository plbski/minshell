/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:41:32 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/24 00:54:29 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

void	show_exec_info(t_data *d, t_token *node, char *arg, char **flg)
{
	const char	*msg[] = {RED "FAIL", GREEN "OK"};
	int			i;

	if (d->fork_child)
		printf("fork[%d] ", d->fork_child);
	printf("\'%s%s%s\' execution was: %s", \
			YELLOW, node->name, RESET, msg[d->last_exit == FCT_OK]);
	printf("[%d] %s - ", d->last_exit, RESET);
	if (arg)
		printf("%sarg%s '%s' ", MENTHA_GREEN, RESET, arg);
	else
		printf("%s[no arg] %s", RED, RESET);
	i = -1;
	if (flg && flg[0])
		printf("%sflags: %s", DB3, RESET);
	else
		printf("%s[no flags]%s", RED, RESET);
	while (flg && flg[++i])
		printf("'%s' ", flg[i]);
	printf("\n");
}

t_token	*show_token_info(t_data *d, t_token *node, char *prx, int spacing)
{
	const char	*args[8] = {prx, node->name, "", "", "", "", "", ""};
	const char	*arg_cols[] = {RED, GREY, DR0, DR1, \
			DR2, CYAN, BLUE, YELLOW, DB4, DB2};
	int			i;

	args[2] = d->types_names[node->type];
	if (node->pipe_out)
		args[3] = node->pipe_out->name;
	if (node->redir)
		args[4] = node->redir->name;
	if (node->red_arg)
		args[5] = node->red_arg->name;
	if (node->nxt_eval)
		args[6] = node->nxt_eval->name;
	if (node->subsh_out)
		args[7] = node->subsh_out->name;
	printf("%s%-7.6s %s", GREEN, args[0], RESET);
	printf("%s%*.15s%s", arg_cols[node->type], -spacing, args[1], RESET);
	printf("%-7d ", node->par);
	i = 1;
	while (++i < 8)
		printf("%-7.6s ", args[i]);
	if (node->rd_fd != -1)
		printf("rdfd: %d", node->rd_fd);
	return (node->next);
}

void	show_tokens_info(t_data *d, t_token *start, char *prfx, int i)
{
	const char	*rg[7] = {"(", "type", \
"pipe", ">", ">_arg", "eval", "sub"};
	int			len;
	t_token		*node;

	len = 15;
	node = token_first(start);
	while (node)
	{
		if (node->name && ft_strlen(node->name) + 2 > len)
			len = ft_strlen(node->name) + 2;
		node = node->next;
	}
	printf("        %s%*s", GREY, -len, "name");
	while (++i < 7)
		printf("%-7s ", rg[i]);
	printf("%s\n", RESET);
	node = token_first(start);
	while (node)
	{
		node = show_token_info(d, node, prfx, len);
		printf("\n");
	}
	printf("\n");
}

void	show_cmd_status(t_data *d, t_token *node)
{
	int	len;

	len = ft_strlen(node->name) + 2;
	if (len < 15)
		len = 15;
	show_token_info(d, node, "RUN", len);
	if (d->last_exit == FCT_FAIL)
		printf("exit status: \033[31mFAIL\033[0m)");
	else
		printf("exit status: \033[32mSUCCESS\033[0m)");
	if (d->fork_child)
		printf("fork process index[%d]", d->fork_child);
	printf("\n");
}

void	show_char_array(char *arr_name, char **arr)
{
	int	i;

	printf("%s%s[%d] > %s", GREY, arr_name, get_arr_len((void **)arr), RESET);
	i = -1;
	while (arr[++i])
		printf("'%s%s%s' ", MENTHA_GREEN, arr[i], RESET);
	printf("\n");
}
