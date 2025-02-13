/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 22:27:52 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/13 14:50:15 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	requires_arg(t_token *node)
{
	return (node->type == tk_red_app || node->type == tk_red_in || \
	node->type == tk_red_out || node->type == tk_pipe || \
	node->type == tk_logical || node->type == tk_hered);
}

int	validate_token(t_data *d, t_token *node)
{
	t_tktype	typ;

	typ = node->type;
	if (!node->prv && (typ != tk_command && typ != tk_exec && \
	typ != tk_hered && !chr_amnt(node->name, '=')))
	{
		printf("%d\n", node->type);
		ft_dprintf(2, "msh: command not found: %s\n", node->name);
		d->last_exit_st = CMD_NOT_FOUND;
		return (0);
	}
	if (typ == tk_argument && !chr_amnt(node->name, '=') && \
	(!node->prv || node->prv->type != tk_exec || node->prv->type != tk_command))
	{
		ft_dprintf(2, "msh: command not found: %s\n", node->name);
		d->last_exit_st = CMD_NOT_FOUND;
		return (0);
	}
	if (requires_arg(node) && !node->next)
	{
		ft_dprintf(2, "msh: parse error near \'%s\'\n", node->name);
		d->last_exit_st = FCT_FAIL;
		return (0);
	}
	return (1);
}
