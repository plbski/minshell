/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   man.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:14:04 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/15 00:17:30 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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

int	man(t_data *d, char *prompt_line)
{
	char	*arg_name;
    char    *arg_with_txt;
	char	*full_path;

	arg_name = ft_remove_prefix(prompt_line, "man ");
	if (!arg_name)
		return (0);
    arg_with_txt = ft_strjoin(arg_name, ".txt");
    if (!arg_with_txt)
        return (0);
    free(arg_name);
	full_path = ft_strjoin(d->doc_wd, arg_with_txt);
	free(arg_with_txt);
	if (!full_path)
		return (0);
	if (access(full_path, F_OK) == -1)
		printf("file not in %s\n", full_path);
	open_doc_content(full_path);
	free(full_path);
	return (1);
}
