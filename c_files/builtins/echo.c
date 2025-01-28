/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plbuet <plbuet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/28 20:58:38 by plbuet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	write_at_abs_path(char *content, char *path, int flags)
{
	int		fd;

	fd = open(path, flags, 0644);
	if (fd == -1)
		return (close(fd), 0);
	write(fd, content, ft_strlen(content));
	close(fd);
	return (1);
}

int	write_at_rel_path(t_data *d, char *content, char *file_name)
{
	char	*full_path;
	int		fd;

	printf("CREATING FILE\n");
	full_path = ft_strjoin(d->cwd, file_name);
	printf("%s\n", full_path);
	fd = open(full_path, O_CREAT | O_APPEND | 0644);
	if (fd == -1)
		return (0);
	write(fd, content, ft_strlen(content));
	return (1);
}

int	exec_echo(char *str, char *next_str)
{
	if (is_same_string(str, "-n"))
		return (1);
	printf("%s", str);
	if (next_str && !is_same_string(next_str, "-n"))
		printf(" ");
	return (0);
}

int	echo(t_data *d, char *arg, char **flags, int status __attribute__((unused)))
{
	int	i;
	int	n_flag;

	(void)d;
	n_flag = 0;
	if (!arg)
	{
		printf("\n");
		return (FCT_SUCCESS);
	}
	n_flag = exec_echo(arg, flags[0]);
	i = -1;
	while (flags && flags[++i])
	{
		if (exec_echo(flags[i], flags[i + 1]))
			n_flag = 1;
	}
	if (!n_flag)
		printf("\n");
	return (FCT_SUCCESS);
}
