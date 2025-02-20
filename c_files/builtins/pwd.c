/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:31:30 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/18 15:09:04 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

int	pwd(t_data *d, char *arg, char **flags, int status)
{
	(void)status;
	(void)flags;
	(void)arg;
	if (printf("%s\n", d->cwd) != -1)
		return (FCT_OK);
	return (FCT_FAIL);
}
