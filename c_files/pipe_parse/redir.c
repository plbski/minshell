/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/30 12:56:54 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	get_fd(t_data *d, char *file_path, t_redir_type r_type)
{
	int	fd;

	if (r_type == APPEND)
		fd = open(file_path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (r_type == OUT)
		fd = open(file_path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(file_path, O_RDONLY);
	if (fd == -1)
		custom_exit(d, "erreur dup2", NULL, EXIT_FAILURE);
	return (fd);
}

void	create_file(t_data *d, char *file_name, t_redir_type r_type)
{
	char	*path;
	int		fd;
	int		dup_target;

	fd = 0;
	while (*file_name == ' ')
		file_name++;
	if (!*file_name)
		custom_exit(d, "error in redir", NULL, EXIT_FAILURE);
	path = ft_str_mega_join(d->cwd, "/", file_name, NULL);
	!path && (custom_exit(d, "error in redir", NULL, EXIT_FAILURE));
	fd = get_fd(d, path, r_type);
	if ((r_type == APPEND || r_type == OUT))
		dup_target = STDOUT_FILENO;
	else
		dup_target = STDIN_FILENO;
	if (dup2(fd, dup_target) == -1)
		custom_exit(d, "erreur dup2", NULL, EXIT_FAILURE);
	fd && (d->fd = fd);
}

int	execute_redir(t_data *d, char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] && (prompt[i] != '>' && prompt[i] != '<'))
		i++;
	if (!prompt[i])
		custom_exit(d, "Messed up something in redir", NULL, EXIT_FAILURE);
	if (prompt[i] == '>' && prompt[i + 1] == '>')
		create_file(d, prompt + (i + 2), APPEND);
	else if (prompt[i] == '<' && prompt[i + 1] == '<')
		heredoc(prompt + (i + 2), d, "heredoc> ", 0);
	else if (prompt[i] == '>')
		create_file(d, prompt + (i + 1), OUT);
	else if (prompt[i] == IN)
		create_file(d, prompt + (i + 1), IN);
	prompt[i] = '\0';
	return (1);
}
