/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 22:27:52 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/18 01:10:24 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

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
	if (!node->prv && (typ != tk_command && \
	typ != tk_hered && !chr_amnt(node->name, '=')))
	{
		printf("%d\n", node->type);
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

int	is_valid_identifier(char *arg)
{
	int	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 0;
	while (arg[++i])
	{
		if (!ft_isalpha(arg[i]) && !ft_isdigit(arg[i]) && arg[i] != '_')
			return (0);
	}
	return (1);
}

t_token	*get_next_redir(t_token *d)
{
	t_token	*node;

	if (!d)
		return (NULL);
	node = d->next;
	while (node)
	{
		if (node->type != tk_argument)
			break ;
		node = node->next;
	}
	if (node && node->is_redir)
		return (node);
	return (NULL);
}

void	set_redir_args(t_token *tok)
{
	t_token	*next_redir;

	while (tok)
	{
		tok->redir = NULL;
		if (tok->type == tk_command)
		{
			next_redir = get_next_redir(tok);
			if (!next_redir || next_redir->par != tok->par)
			{
				tok = tok->next;
				continue ;
			}
			tok->redir = next_redir;
			if (tok->redir->type != tk_red_in)
				tok->red_arg = tok->redir->next;
			else
				tok->red_arg = get_last_arg(tok);
		}
		tok = tok->next;
	}
}
