/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   man.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:14:04 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/24 13:56:14 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	open_doc_content(char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("\n");
}

int	man(t_data *d, char *arg, char *flags, int status)
{
	(void)d;
	(void)flags;
	(void)status;

	if (access(arg, F_OK) == -1)
		printf("file not in %s\n", arg);
	open_doc_content(arg);
	return (1);
}
