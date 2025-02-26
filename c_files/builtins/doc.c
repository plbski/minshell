/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:14:04 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/18 15:09:04 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static void	open_doc_content(char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return ;
	printf("\n			Minishell Commands Manual\n\n");
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("\n\n");
}

static int	execute_doc(t_data *d, char *path)
{
	if (!path)
		custom_exit(d, "man path alloc failed", NULL, EXIT_FAILURE);
	if (access(path, F_OK) == -1)
	{
		printf("No manual entry for %s\n", path);
		return (FCT_FAIL);
	}
	open_doc_content(path);
	return (FCT_OK);
}

int	doc(t_data *d, char *arg, char **flags, int status)
{
	char	*path;
	int		fct_ret;

	(void)status;
	(void)flags;
	if (!arg)
	{
		ft_dprintf(2, "What minishell page do you want?\n");
		return (FCT_OK);
	}
	path = ft_megajoin(d->man_wd, arg, ".txt", NULL);
	if (!path)
		custom_exit(d, "man path alloc failed", NULL, EXIT_FAILURE);
	fct_ret = execute_doc(d, path);
	free(path);
	return (fct_ret);
}
