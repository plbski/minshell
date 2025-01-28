/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 01:33:24 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/28 01:33:32 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_data	t_datas[1024];
	int				status;
	t_data			*d;
	char			*ret;

	if (fd < 0)
		return (NULL);
	d = &t_datas[fd];
	if (contains(d->leftover, '\n'))
		return (handle_leftover(d));
	status = update_fd(d, fd, 0, 0);
	if (status <= 0)
	{
		ret = NULL;
		if (status == -1)
			while (d->leftover[++status])
				d->leftover[status] = '\0';
		if (d->leftover[0])
			ret = ft_strdup(d->leftover);
		d->leftover[0] = '\0';
		return (ret);
	}
	return (ft_strdup(d->buffer));
}
