/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/21 12:49:39 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	create_file(t_data *d, char *content, char *file_name)
{
	char	*full_path;
	int		fd;

	printf("CREATING FILE\n");
	full_path = ft_strjoin(d->cwd, file_name);
	printf("%s\n", full_path);
	fd = open(full_path, O_CREAT, O_TRUNC, 0644);
	if (fd == -1)
		return (0);
	write(fd, content, ft_strlen(content));
	return (1);
}
