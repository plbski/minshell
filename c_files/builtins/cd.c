/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:29:41 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/21 01:10:12 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static char	*get_cd_path(t_data *d, char *arg)
{
	if (!arg || same_str(arg, "--"))
		return (ms_strdup(d, d->home_wd));
	if (same_str(arg, "-"))
	{
		if (!d->prev_cwd)
			return (printf("msh cd: OLDPWD not set\n"), NULL);
		printf("%s\n", d->prev_cwd);
		return (ms_strdup(d, d->prev_cwd));
	}
	return (ms_strdup(d, arg));
}

int	cd(t_data *d, char *arg, char **flags, int status)
{
	char	*path;

	status = FCT_FAIL;
	if (flags && flags[0])
		return (ft_dprintf(2, "msh: cd: too many arguments\n"), status);
	path = get_cd_path(d, arg);
	if (!path)
		return (status);
	if (chdir(path) == -1)
	{
		ft_dprintf(2, "msh: cd: %s: No such file or directory\n", path);
		free(path);
		return (status);
	}
	update_cwd(d);
	free(path);
	return (FCT_OK);
}
