/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:37:20 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/17 17:59:04 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

t_token	*redirect_pipe(t_data *d, t_token *nxt, int pipefd[2], int redir)
{
	int		fd;
	char	*output;

	output = get_fd_content(d, pipefd[0]);
	if (!output)
	{
		if (d->debug_mode)
			printf("no output found for redir\n");
		return (nxt);
	}
	while (nxt && nxt->type == tk_argument)
	{
		fd = get_fd(d, nxt->name, redir);
		if (fd >= 0)
		{
			write(fd, output, ft_strlen(output));
			close(fd);
		}
		nxt = nxt->next;
	}
	free(output);
	return (nxt);
}

t_token	*skip_type(t_token *tok, t_tktype type_to_skip)
{
	while (tok && tok->type == type_to_skip)
		tok = tok->next;
	return (tok);
}

