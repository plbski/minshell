/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tools3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:03:05 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/31 18:04:35 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	*ms_strjoin(t_data *d, char const *s1, char const *s2)
{
	int		i;
	int		u;
	char	*joined;

	joined = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined)
	{
		printf("%s - %s > ", s1, s2);
		custom_exit(d, "alloc failed in strjoin", NULL, EXIT_FAILURE);
	}
	i = 0;
	u = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	while (s2[u])
	{
		joined[i + u] = s2[u];
		u++;
	}
	joined[i + u] = '\0';
	return (joined);
}

char	*ms_strdup(t_data *d, const char	*s1)
{
	char	*dst;
	int		i;
	int		len;

	len = ft_strlen(s1);
	dst = (char *)malloc(len + 1);
	if (!dst)
	{
		printf("%s > ", s1);
		custom_exit(d, "alloc failed in strdup", NULL, EXIT_FAILURE);
	}
	i = 0;
	while (i < len)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

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

int	is_all_digit(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}
