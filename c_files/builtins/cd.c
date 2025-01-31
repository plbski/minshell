/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:29:41 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/30 21:31:38 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	*get_cd_path(t_data *d, char *arg)
{
	char	*path;

	path = NULL;
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
			return (printf("msh cd: OLDPWD not set\n"), NULL);
		path = ft_strdup(d->prev_cwd);
		if (!path)
			custom_exit(d, "cd path alloc fail", NULL, EXIT_FAILURE);
		printf("%s\n", path);
	}
	else
		path = ft_strdup(arg);
	if (!path)
		custom_exit(d, "cd path alloc fail", NULL, EXIT_FAILURE);
	return (path);
}

int	cd(t_data *d, char *arg, char **flags, int status)
{
	char	*path;

	(void)status;
	if (flags && flags[0])
		return (printf("cd: string not in pwd: %s\n", arg), 0);
	path = get_cd_path(d, arg);
	if (!path)
		return (FCT_FAIL);
	if (chdir(path) == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		free(path);
		return (FCT_FAIL);
	}
	update_cwd(d);
	free(path);
	return (FCT_SUCCESS);
}
