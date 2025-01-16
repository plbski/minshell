/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:38:22 by pbuet             #+#    #+#             */
/*   Updated: 2025/01/15 18:33:27 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*check_path(t_data *d, char *arg)
{
	char	*full_path;
	int		i;

	i = 0;
	if (arg[i] != '/')
			full_path = path(d->cwd, "/");
		full_path = path(full_path, &arg[i]);
		printf("%s\n", full_path);
		if (access(full_path, F_OK) == -1)
		{
			printf("path not found %s", full_path);
			free(full_path);
			return (NULL);
		}
	return (full_path);
}
void	double_point(t_data *d, char *arg)
{
	int		i;

	if ( !arg || arg[0] == '/')
	{
		i = ft_strlen(d->cwd);
		while (i > 1 && d->cwd[i] != '/')
			i --;
		d->cwd[i] = '\0';
		if (arg[1])
			get_path(&arg[1], d);
	}
}

char	*path(char *path, char *arg)
{
	char	*tmp;

	tmp = path;
	path = ft_strjoin(tmp, arg);
	return (path);
}

void	get_path(char *arg, t_data *d)
{
	char	*full_path;
	int		i;

	i = 0;
	while (arg[i] && arg[i] == 32)
		i ++;
	if (!arg[i])
	{
		full_path = d->cwd;
		d->cwd = ft_strdup(d->home);
		free(full_path);
	}
	else if (ft_strncmp("..", &arg[i], 2) == 0)
		double_point(d, arg[i ]);
	else
	{
		if (arg[i] != '/')
			full_path = path(d->cwd, "/");
		full_path = path(full_path, &arg[i]);
		printf("%s\n", full_path);
		if (access(full_path, F_OK) == -1)
		{
			printf("path not found %s", full_path);
			free(full_path);
			return;
		}
		else
			d->cwd = full_path;
	}
}

void	ft_cd(t_data *d, char *arg)
{
	printf("BONJOUR\n");
	get_path(&arg[2], d);
}
