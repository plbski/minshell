/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:31:30 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/11 13:06:24 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	pwd(t_data *d, char *arg, char **flags, int status)
{
	(void)status;
	(void)flags;
	(void)arg;
	if (printf("%s\n", d->cwd) != -1)
		return (FCT_SUCCESS);
	return (FCT_FAIL);
}
