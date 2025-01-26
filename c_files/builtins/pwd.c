/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:31:30 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/26 12:39:31 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	pwd(t_data *d, char *arg, char **flags, int status)
{
	(void)status;
	if (arg || flags)
	{
		printf("pwd: too many arguments\n");
		return (0);
	}
	printf("%s\n", d->cwd);
	return (1);
}
