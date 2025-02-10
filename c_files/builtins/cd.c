/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:29:41 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/10 17:11:52 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static char	*get_cd_path(t_data *d, char *arg)
{
	char	*path;

	path = NULL;
	if (!arg || !ft_strncmp(arg, "~", 2))
	{
		if (d->home_wd == NULL)
			custom_exit(d, "Home wd not found", NULL, EXIT_FAILURE);
		else
			path = ms_strdup(d, d->home_wd);
	}
	else if (!ft_strncmp(arg, "-", 2))
	{
		if (!d->prev_cwd)
			return (printf("msh cd: OLDPWD not set\n"), NULL);
		path = ms_strdup(d, d->prev_cwd);
		printf("%s\n", path);
	}
	else
		path = ms_strdup(d, arg);
	if (!path)
		custom_exit(d, "cd path alloc fail", NULL, EXIT_FAILURE);
	return (path);
}

int	cd(t_data *d, char *arg, char **flags, int status)
{
	char	*path;

	(void)status;
	if (flags && flags[0])
		return (printf("cd: too many arguments\n"), 0);
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
