/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:41:32 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/17 16:50:57 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	show_exec_info(t_data *d, t_token *node, char *arg, char **flg)
{
	int	i;

	i = -1;
	if (d->last_exit_st == FCT_FAIL)
		printf("%s%s execution: %s", RED, node->name, "FAIL");
	else
		printf("%s%s execution: %s", GREEN, node->name, "SUCCESS");
	printf("[%d] %s", d->last_exit_st, RESET);
	if (arg)
		printf("[%s", arg);
	while (flg && flg[++i])
	{
		if (i == 0)
			printf(", ");
		printf("%s", flg[i]);
		if (flg[i + 1])
			printf(", ");
	}
	if (arg)
		printf("]");
	printf("\n");
}

void	show_token_info(t_data *d, t_token *node, char *prx, char *sufx)
{
	const char	*args[9] = {prx, "", "", "", "", "", "", "", sufx};
	const char	*arg_cols[] = {RED, GREY, BLUE, PRP_LAV, DR2, CYAN, BLUE, YELLOW};
	int			i;
	char		*par;

	args[1] = node->name;
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
	printf("%s%-10s %s", GREEN, args[0], RESET);
	printf("%s%-10s %s", arg_cols[node->type], args[1], RESET);
	i = 1;
	while (++i < 9)
		printf("%-10s %s", args[i], RESET);
	printf("\n");
	free(par);
}

void	show_tokens_info(t_data *d, t_token *node, char *prfx, char *suffix)
{
	printf("	  %-5s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", \
GREY, "name", "type", "brk", "pipe", "redir", "red_arg", "nxt eval", RESET);
	node = token_first(node);
	while (node)
	{
		show_token_info(d, node, prfx, suffix);
		node = node->next;
	}
	printf("\n");
}

void	show_cmd_status(t_data *d, t_token *node)
{
	char	*suffix;

	if (d->last_exit_st == FCT_FAIL)
		suffix = ft_strdup("(curr. ext st > \033[31mFAIL\033[0m)");
	else
		suffix = ft_strdup("(curr. ext st > \033[32mSUCCESS\033[0m)");
	show_token_info(d, node, "eval", suffix);
	free(suffix);
}
