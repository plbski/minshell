/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:29:41 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/17 23:20:31 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static char	*get_cd_path(t_data *d, char *arg)
{
	char	*path;

	if (!arg)
		arg = d->home_wd;
	path = NULL;
	if (!ft_strncmp(arg, "-", 2))
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
		return (ft_dprintf(2, "msh: cd: too many arguments\n"), 0);
	path = get_cd_path(d, arg);
	if (!path)
		return (FCT_FAIL);
	if (chdir(path) == -1)
	{
		ft_dprintf(2, "msh: cd: %s: No such file or directory\n", path);
		free(path);
		return (FCT_FAIL);
	}
	update_cwd(d);
	free(path);
	return (FCT_SUCCESS);
}
