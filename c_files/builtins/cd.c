/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:29:41 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/26 17:59:02 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	cd(t_data *d, char *arg, char **flags, int status _UNUSED)
{
	char	*path;

	if (flags && flags[1])
		return (printf("cd: string not in pwd: %s\n", flags[1]), 0);
	if (!arg || !ft_strncmp(arg, "~", 2))
	{
		if (d->home_wd == NULL)
			custom_exit(d, "Home wd not found", NULL, EXIT_FAILURE);
		else
			path = ft_strdup(d->home_wd);
	}
	else if (!ft_strncmp(arg, "-", 2))
	{
		if (!d->prev_cwd)
			return (printf("msh cd: OLDPWD not set\n"), 0);
		path = ft_strdup(d->prev_cwd);
		printf("%s\n", path);
	}
	else
		path = ft_strdup(arg);
	if (chdir(path) == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		return (free(path), 0);
	}
	else
		update_cwd(d);
	return (free(path), 1);
}
