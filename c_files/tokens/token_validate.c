/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 23:31:57 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/03/04 12:39:21 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static int	validate_tk_sep_pipe(t_tktype pv, t_tktype nxt)
{
	if (pv == tk_logical || pv == tk_cmdsep || pv == tk_pipe || (int)pv == -1)
		return (0);
	if (nxt == tk_logical || nxt == tk_cmdsep || nxt == tk_pipe)
		return (0);
	return (1);
}

static int	validate_tk_logical(t_tktype prv, t_tktype nx)
{
	if (prv == tk_logical || prv == tk_cmdsep || prv == tk_pipe)
		return (0);
	if (nx == tk_logical || nx == tk_cmdsep || nx == tk_pipe || (int)nx == -1)
		return (0);
	return (1);
}

static int	validate_tk_redir(t_tktype nx, int nxt_redir)
{
	if (nx == tk_logical || nx == tk_cmdsep || nx == tk_pipe || nxt_redir)
		return (0);
	if ((int)nx == -1)
		return (0);
	return (1);
}

static int	validate_tk_type(t_token *tk)
{
	t_tktype	prv;
	t_tktype	nxt;
	int			nxt_is_redir;

	prv = -1;
	nxt = -1;
	nxt_is_redir = 0;
	if (tk->next)
		nxt_is_redir = tk->next->is_rd;
	if (tk->prv)
		prv = tk->prv->type;
	if (tk->next)
		nxt = tk->next->type;
	if (tk->type == tk_logical)
		return (validate_tk_logical(prv, nxt));
	else if (tk->type == tk_pipe || tk->type == tk_cmdsep)
		return (validate_tk_sep_pipe(prv, nxt));
	else if (tk->is_rd)
		return (validate_tk_redir(nxt, nxt_is_redir));
	else
		return (1);
}

int	validate_token_sequence(t_data *d, t_token *tk)
{
	while (tk)
	{
		if (tk->type == tk_arg && tk->prv && tk->prv->type == tk_cmdsep)
			tk->type = tk_cmd;
		if ((tk->type == tk_logical || tk->type == tk_pipe || \
				tk->type == tk_cmdsep || tk->is_rd) && !validate_tk_type(tk))
			break ;
		tk = tk->next;
	}
	if (!tk)
		return (1);
	d->last_exit = FCT_FAIL;
	return (ft_dprintf(2, "msh: parse error near token '%s' \n", tk->name), 0);
}
