/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:31:30 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/30 20:41:31 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	pwd(t_data *d, char *arg, char **flags, int status)
{
	(void)arg;
	(void)flags;
	(void)status;
	if (printf("%s\n", d->cwd) != -1)
		return (FCT_SUCCESS);
	return (FCT_FAIL);
}
