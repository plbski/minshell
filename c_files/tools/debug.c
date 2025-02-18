/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:41:32 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/18 02:07:31 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

void	show_exec_info(t_data *d, t_token *node, char *arg, char **flg)
{
	int	i;

	i = -1;
	if (d->last_exit_st == FCT_FAIL)
		printf("%s%s exect: %s", RED, node->name, "FAIL");
	else
		printf("%s%s exect: %s", GREEN, node->name, "SUCCESS");
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
	const char	*args[10] = {prx, node->name, "", "", "", "", "", "", "", sufx};
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
	printf("%s%-7.6s %s", arg_cols[node->type], args[1], RESET);
	i = 1;
	while (++i < 10)
		printf("%-7.6s %s", args[i], RESET);
	printf("\n");
	free(par);
}

void	show_tokens_info(t_data *d, t_token *node, char *prfx, char *suffix)
{
	const char	*rg[8] = {"name", "type", "par", "pipe", \
			"redir", "rd_arg", "eval", "subs"};
	int			i;

	printf("        %s", GREY);
	i = -1;
	while (++i < 8)
		printf("%-7s ", rg[i]);
	printf("%s\n", RESET);
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
