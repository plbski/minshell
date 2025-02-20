/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:41:32 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/18 16:29:11 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

void	show_exec_info(t_data *d, t_token *node, char *arg, char **flg)
{
	const char	*msg[] = {RED "FAIL", GREEN "OK"};
	int			i;

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

void	show_token_info(t_data *d, t_token *node, char *prx, int spacing)
{
	const char	*args[9] = {prx, node->name, "", "", "", "", "", "", ""};
	const char	*arg_cols[] = {RED, GREY, DR0, DR1, DR2, CYAN, BLUE, YELLOW};
	int			i;
	char		*par;

	args[2] = d->types_names[node->type];
	par = ft_itoa(node->par);
	args[3] = par;
	if (node->pipe_out)
		args[4] = node->pipe_out->name;
	if (node->redir)
		args[5] = node->redir->name;
	if (node->red_arg)
		args[6] = node->red_arg->name;
	if (node->nxt_eval)
		args[7] = node->nxt_eval->name;
	if (node->subsh_out)
		args[8] = node->subsh_out->name;
	printf("%s%-7.6s %s", GREEN, args[0], RESET);
	printf("%s%*.15s%s", arg_cols[node->type], -spacing, args[1], RESET);
	i = 1;
	while (++i < 9)
		printf("%-7.6s %s", args[i], RESET);
	free(par);
}

void	show_tokens_info(t_data *d, t_token *start, char *prfx)
{
	const char	*rg[8] = {"name", "type", "par", "pipe", \
			"redir", "rd_arg", "eval", "subs"};
	int			i;
	int			max_len;
	t_token		*node;

	max_len = 7;
	node = token_first(start);
	while (node)
	{
		if (node->name && ft_strlen(node->name) + 2 > max_len)
			max_len = ft_strlen(node->name) + 2;
		node = node->next;
	}
	if (max_len > 15)
		max_len = 15;
	printf("        %s%*s", GREY, -max_len, rg[0]);
	i = 0;
	while (++i < 8)
		printf("%-7s ", rg[i]);
	printf("%s\n", RESET);
	node = token_first(start);
	while (node)
	{
		show_token_info(d, node, prfx, max_len);
		printf("\n");
		node = node->next;
	}
	printf("\n");
}

void	show_cmd_status(t_data *d, t_token *node)
{
	int	len;

	len = ft_strlen(node->name) + 2;
	if (len < 7)
		len = 7;
	else if (len > 15)
		len = 15;
	show_token_info(d, node, "RUN", len);
	if (d->last_exit == FCT_FAIL)
		printf("exit status: \033[31mFAIL\033[0m)");
	else
		printf("exit status: \033[32mSUCCESS\033[0m)");
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
