/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:29:41 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/24 13:52:57 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	cd(t_data *d, char *arg, char *flags, int status)
{
	char	*path;

	(void)flags;
	(void)status;
	path = ft_strdup(arg);
	if (!ft_strncmp(arg, "~", 2) && d->home_wd != NULL)
	{
		free(path);
		path = ft_strdup(d->home_wd);
	}
	if (!ft_strncmp(arg, "-", 2) && d->prev_cwd != NULL)
	{
		free(path);
		path = ft_strdup(d->prev_cwd);
	}
	if (chdir(path) == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		return (0);
	}
	else
		update_cwd(d);
	free(path);
	return (1);
}
