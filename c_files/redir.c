/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/22 21:12:42 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	create_file(t_data *d, char *file_name, int end)
{
	char	*full_path;
	int		fd;

	// printf("CREATING FILE\n");
	while(*file_name == ' ')
		file_name++;
	file_name = ft_strjoin("/", file_name);
	full_path = ft_strjoin(d->cwd, file_name);
	// printf("%s\n", full_path);
	if (end == 1)
		fd = open(full_path, O_WRONLY| O_APPEND |O_CREAT, 0644);
	else 
		fd = open(full_path, O_WRONLY | O_TRUNC |O_CREAT, 0644);
	if (fd == -1)
		exit(0);
	return (fd);
}

static	int check(t_data *d, char *prompt)
{
	int	i;

	i = 0;
	while ((prompt[i] != '>' && prompt[i] != '<') && prompt[i])
		i ++;
	if ((prompt[i] == '>') && (prompt[i + 1] == '>'))
		return(create_file(d, prompt + (i + 2), 1));
	else if ((prompt[i] == '<') && (prompt[i + 1] == '<'))
		return (0);
	else if (prompt[i] == '>')
			return(create_file(d, prompt + (i + 1), 0));
	else if (prompt[i] == '<')
		return (0);
	else
		return (0);
}
void	echo(t_data *d, char *prompt)
{
	int fd;
	int i;

	i = 0;
	prompt = ft_remove_prefix(prompt, "echo", 1);
	fd = check(d, prompt);
	while ((prompt[i] != '>' && prompt[i] != '<') && prompt[i])
	{
		i ++;
		write(fd, prompt,1);
	}
	write(fd, "\n", 1);
}

