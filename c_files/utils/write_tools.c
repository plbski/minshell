/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:06:54 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/03 10:45:14 by giuliovalen      ###   ########.fr       */
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

char	*replace_str(t_data *d, char *str, char *remove, char *replace)
{
	char	*new_str;
	int		i;
	int		j;

	if (!str || !remove)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		j = 0;
		while (remove[j] && remove[j] == str[i + j])
			j++;
		if (remove[j])
			continue ;
		i += j;
		j = 0;
		new_str = malloc(ft_strlen(str) - i + 1);
		if (!new_str)
			custom_exit(d, "alloc in str_prefix", NULL, EXIT_FAILURE);
		while (str[i])
			new_str[j++] = str[i++];
		new_str[j] = '\0';
		return (ms_strjoin(d, replace, new_str));
	}
	return (ms_strdup(d, str));
}
