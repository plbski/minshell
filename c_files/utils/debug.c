/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:41:32 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/04 16:18:22 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	show_exec_info(t_data *d, t_token *node, char *arg, char **flg)
{
	int	i;

	i = -1;
	if (d->last_exit_status == FCT_FAIL)
		printf("%s%s execution: %s", RED, node->name, "FAIL");
	else
		printf("%s%s execution: %s", GREEN, node->name, "SUCCESS");
	printf("[%d] %s", d->last_exit_status, RESET);
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

void	show_token_info(t_data *d, t_token *node, char *prefix, char *suffix)
{
	char		pipe_out[30];
	char		arg_color[30];

	if (node->type == tk_command || node->type == tk_exec)
		ft_strlcpy(arg_color, RED, 30);
	else if (node->type == tk_argument)
		ft_strlcpy(arg_color, YELLOW, 30);
	else if (node->type == tk_pipe)
		ft_strlcpy(arg_color, CYAN, 30);
	else if (node->type == tk_logical)
		ft_strlcpy(arg_color, BLUE, 30);
	else
		ft_strlcpy(arg_color, GREY, 30);
	if (node->pipe_out)
		ft_strlcpy(pipe_out, node->pipe_out->name, 30);
	else
		ft_strlcpy(pipe_out, " ", 30);
	printf("%s%-8s%s%-8s %s%-10s%s %-6d %-10s%-8s\n", \
		GREEN, prefix, RESET, node->name, arg_color, \
		d->types_names[node->type], RESET, node->par, pipe_out, suffix);
}

void	show_tokens_info(t_data *d, t_token *node, char *prfx, char *suffix)
{
	printf("	%s%-8s %-10s %-6s %-5s%s\n", \
		GREY, "name", "type", "brk", "pipe", RESET);
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

	if (d->last_exit_status == FCT_FAIL)
		suffix = ft_strdup("(curr. ext st > \033[31mFAIL\033[0m)");
	else
		suffix = ft_strdup("(curr. ext st > \033[32mSUCCESS\033[0m)");
	show_token_info(d, node, "eval", suffix);
	free(suffix);
}
