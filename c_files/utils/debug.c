/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:41:32 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/03 12:02:27 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	show_exec_info(t_data *d, t_token *node, char *arg, char **flg)
{
	int	i;

	show_token_info(d, node, "executed", " | ");
	printf("arg: \"%s%s%s\", ", YELLOW, arg, RESET);
	i = -1;
	while (flg && flg[++i])
		printf("flag[%d] \"%s%s%s\", ", i, YELLOW, flg[i], RESET);
	if (d->last_exit_status == FCT_FAIL)
		printf("cmd return: %s%s", RED, "FAIL");
	else
		printf("cmd return: %s%s", GREEN, "SUCCESS");
	printf("[%d]\n\n%s", d->last_exit_status, RESET);
}

void	show_token_info(t_data *d, t_token *node, char *prfx, char *suffix)
{
	printf("%s%s%s: \"%s\" type \"%s\" par %d%s", \
CYAN, prfx, RESET, node->name, d->types_names[node->type], node->par, suffix);
}

void	show_tokens_info(t_data *d, t_token *node, char *prfx)
{
	node = token_first(node);
	while (node)
	{
		show_token_info(d, node, prfx, "\n");
		node = node->next;
	}
	printf("\n");
}

void	show_cmd_status(t_data *d, t_token *node)
{
	if (d->last_exit_status == FCT_FAIL)
		printf("(exit status: %s) %s", "\033[31mFAIL", RESET);
	else
		printf("(exit status: %s) %s", "\033[32mSUCCESS", RESET);
	show_token_info(d, node, "evaluating", "\n");
}
