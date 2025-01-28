/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/28 18:38:05 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	create_file(t_data *d, char *file_name, int redir)
{
	char	*full_path;
	int		fd;

	fd = 0;
	while(*file_name == ' ')
		file_name++;
	file_name = ft_strjoin("/", file_name);
	full_path = ft_strjoin(d->cwd, file_name);
	if (redir == 1)
		fd = open(full_path, O_WRONLY| O_APPEND |O_CREAT, 0644);
	else if (redir == 2)
		fd = open(full_path, O_WRONLY | O_TRUNC |O_CREAT, 0644);
	else
		fd = open(full_path, O_RDONLY);
	if (fd == -1)
		custom_exit(d, "erreur dup2", NULL, EXIT_FAILURE);
	if (redir == 1 | redir == 2)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			custom_exit(d, "erreur dup2", NULL, EXIT_FAILURE);
	}
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			custom_exit(d, "erreur dup2", NULL, EXIT_FAILURE);
	}
	if (fd > 0)
		d->fd = fd;
}

void	heredoc(char *prompt, t_data *d)
{
	char	*line;
	int		pipefd[2];
	int		len;

	while(*prompt == ' ')
		prompt++;
	if (pipe(pipefd) == -1)
		custom_exit(d, "erreur pipe", NULL, EXIT_FAILURE);
	len = 0;
	line = NULL;
	printf("prompt : %s\n", prompt);
	while(1)
	{
		write(1,"heredoc>", 8);
		line = get_next_line(0);
		if (line == NULL)
			custom_exit(d, "erreur gnl", NULL, EXIT_FAILURE);
		line = truncate_at_end(line, '\n');
		len = ft_strlen(line);
		if (ft_strncmp(line, prompt, len) == 0)
			break;
		write(pipefd[1], line, len);
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	close(pipefd[0]);
}

static	void check(t_data *d, char *prompt)
{
	int	i;

	i = 0;
	while ((prompt[i] != '>' && prompt[i] != '<') && prompt[i])
		i ++;
	if ((prompt[i] == '>') && (prompt[i + 1] == '>'))
		create_file(d, prompt + (i + 2), 1);
	else if ((prompt[i] == '<') && (prompt[i + 1] == '<'))
		heredoc(prompt + (i + 2), d);
	else if (prompt[i] == '>')
		create_file(d, prompt + (i + 1), 2);
	else if (prompt[i] == '<')
		create_file(d, prompt + (i + 1), 3);
}

char	*redir(t_data *d, char *prompt)
{
	int	i;

	check(d, prompt);
	i = 0;
	while ((prompt[i] != '>' && prompt[i] != '<') && prompt[i])
		i ++;
	if (prompt[i - 1] == 32)
	{
		i -= 1;
		while (prompt[i] == 32 && i > 0)
			i --;
		i +=1;
	}
	prompt[i] = '\0';
	return (prompt);
}
