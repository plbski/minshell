/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:29:41 by gvalente          #+#    #+#             */
/*   Updated: 2025/03/04 17:14:50 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static char	*get_cd_path(t_data *d, char *arg)
{
	if (!arg || same_str(arg, "--"))
	{
		if (!d->home_wd || d->home_wd[0] == '?')
		{
			if (!arg)
			{
				ft_dprintf(2, "msh: cd: HOME not set\n");
				return (NULL);
			}
			return (ms_strdup(d, arg));
		}
		return (ms_strdup(d, d->home_wd));
	}
	if (same_str(arg, "-"))
	{
		if (!d->prev_cwd)
			return (printf("msh cd: OLDPWD not set\n"), NULL);
		printf("%s\n", d->prev_cwd);
		return (ms_strdup(d, d->prev_cwd));
	}
	return (ms_strdup(d, arg));
}

int	validate_cd(char *path)
{
	if (access(path, F_OK) == -1)
		ft_dprintf(2, "msh: cd: %s: No such file or directory\n", path);
	else if (!is_directory(path))
		ft_dprintf(2, "msh: cd: %s: Not a directory\n", path);
	else if (access(path, X_OK) == -1)
		ft_dprintf(2, "msh: cd: %s: Permission denied\n", path);
	else
		return (1);
	return (0);
}

int	cd(t_data *d, char *arg, char **flags, int status)
{
	char	*path;

	status = FCT_FAIL;
	if (flags && flags[0])
		return (ft_dprintf(2, "msh: cd: too many arguments\n"), status);
	if (same_str(arg, "."))
		return (FCT_OK);
	path = get_cd_path(d, arg);
	if (!path)
		return (status);
	if (!validate_cd(path))
		return (free(path), FCT_FAIL);
	if (chdir(path) == -1)
	{
		free(path);
		return (status);
	}
	update_cwd(d);
	free(path);
	return (FCT_OK);
}
