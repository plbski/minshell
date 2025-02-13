/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 22:27:52 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/13 02:04:35 by gvalente         ###   ########.fr       */
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

void	split_list(t_token *source, t_token **front_ref, t_token **back_ref)
{
	t_token	*fast;
	t_token	*slow;

	slow = source;
	fast = source->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front_ref = source;
	*back_ref = slow->next;
	slow->next = NULL;
	if (*back_ref != NULL)
		(*back_ref)->prv = NULL;
}

t_token	*merge_sorted_lists(t_token *a, t_token *b)
{
	t_token	*result;

	result = NULL;
	if (a == NULL)
		return (b);
	if (b == NULL)
		return (a);
	if (a->par >= b->par)
	{
		result = a;
		result->next = merge_sorted_lists(a->next, b);
		if (result->next != NULL)
			result->next->prv = result;
		result->prv = NULL;
	}
	else
	{
		result = b;
		result->next = merge_sorted_lists(a, b->next);
		if (result->next != NULL)
			result->next->prv = result;
		result->prv = NULL;
	}
	return (result);
}

void	merge_sort_tokens(t_token **head_ref)
{
	t_token	*head;
	t_token	*a;
	t_token	*b;

	head = *head_ref;
	if ((head == NULL) || (head->next == NULL))
		return ;
	split_list(head, &a, &b);
	merge_sort_tokens(&a);
	merge_sort_tokens(&b);
	*head_ref = merge_sorted_lists(a, b);
}
