/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/23 05:23:48 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	write_to_file(t_data *d, char *content, char *file_name)
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

void	echo(t_data *d, char *prompt)
{
	char	*file_name;
	char	*content;

	prompt = remove_char(prompt, '"');
	content = ft_remove_prefix(prompt, "echo ");
	file_name = ft_strstr(prompt, ">>");
	if (file_name)
	{
		free(content);
		content = ft_remove_prefix(prompt, ">>");
		write_to_file(d, content, file_name);
		free(content);
	}
	else
		printf("%s\n", content);
}
