/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   man.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:14:04 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/24 18:15:31 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

#include <termios.h>

void	process_man_menu(void)
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

void	open_doc_content(char *path)
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

int	man(t_data *d, char *arg, char *flags, int status)
{
	char	*full_path;

	(void)d;
	(void)status;
	if (flags)
		return (printf("man: too many arguments\n"), 0);
	full_path = ft_str_mega_join(d->doc_wd, arg, ".txt", NULL);
	if (!full_path)
		custom_exit(d, "man path alloc failed", NULL, 1);
	if (access(full_path, F_OK) == -1)
		printf("file not in %s\n", full_path);
	else
		open_doc_content(full_path);
	free(full_path);
	return (1);
}
