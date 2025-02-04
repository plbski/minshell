/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   man.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:14:04 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/04 10:37:27 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

#include <termios.h>

static void	process_man_menu(void)
{
	struct termios	oldt;
	struct termios	newt;
	char			c;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	fflush(stdout);
	while (1)
	{
		read(STDIN_FILENO, &c, 1);
		if (c == 'q')
			break ;
	}
	printf("\n");
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

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
	printf("\n\n:");
	process_man_menu();
}

static int	execute_man(t_data *d, char *path)
{
	if (!path)
		custom_exit(d, "man path alloc failed", NULL, EXIT_FAILURE);
	if (access(path, F_OK) == -1)
	{
		printf("No manual entry for %s\n", path);
		return (FCT_FAIL);
	}
	open_doc_content(path);
	return (FCT_SUCCESS);
}

int	man(t_data *d, char *arg, char **flags, int status)
{
	char	*path;
	int		i;
	int		fct_ret;

	(void)status;
	path = ft_str_mega_join(d->man_wd, arg, ".txt", NULL);
	if (!path)
		custom_exit(d, "man path alloc failed", NULL, EXIT_FAILURE);
	fct_ret = execute_man(d, path);
	free(path);
	i = -1;
	while (flags[++i])
	{
		path = ft_str_mega_join(d->man_wd, flags[i], ".txt", NULL);
		if (!path)
			custom_exit(d, "man path alloc failed", NULL, EXIT_FAILURE);
		if (execute_man(d, path) == FCT_SUCCESS)
			fct_ret = FCT_SUCCESS;
		free(path);
	}
	return (fct_ret);
}
