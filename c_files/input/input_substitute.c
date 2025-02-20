/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_substitute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:44:39 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/19 16:57:07 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

void	handle_child(t_data *d, char *value, int *pipefd)
{
	d->fork_child = 1;
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	exec_input(d, value);
	free(value);
	custom_exit(d, "null", NULL, d->last_exit);
}

char	*get_cmd_subst(t_data *d, char *str, int *i, char *ret_cmd)
{
	char	*par_value;
	int		status;
	int		pid;
	int		pipefd[2];

	*i += 2;
	par_value = copy_until_char(d, str, i, ")");
	if (pipe(pipefd) == -1)
		custom_exit(d, "pipe in cmdsubstr", NULL, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		custom_exit(d, "fork in cmdsubstr", NULL, EXIT_FAILURE);
	if (pid == 0)
		handle_child(d, par_value, pipefd);
	waitpid(pid, &status, 0);
	close(pipefd[1]);
	setstr(d, &ret_cmd, get_fd_content(d, pipefd[0]));
	close(pipefd[0]);
	if (!ret_cmd)
		return (ft_strdup(""));
	if (ret_cmd[ft_strlen(ret_cmd) - 1] == '\n')
		ret_cmd[ft_strlen(ret_cmd) - 1] = '\0';
	while (*i > 0 && str[*i] && str[(*i - 1)] != ')')
		(*i)++;
	return (ret_cmd);
}

char	*replace_split(t_data *d, char *split, int start)
{
	char	*subst;
	char	*new_str;
	int		j;

	j = start;
	subst = get_cmd_subst(d, split, &j, NULL);
	if (!subst)
		subst = ft_strdup("");
	while (j - 1 >= 0 && split[j] && split[j - 1] != ')')
		j++;
	new_str = str_insert(split, start, j - 1, subst);
	if (d->debug_mode)
		printf("subst: \"%s\" with \"%s\"\n", split, new_str);
	if (new_str)
		setstr(d, &split, new_str);
	free(subst);
	return (new_str);
}

void	solve_cmd_substitutes(t_data *d, char ***spl)
{
	int		i;
	int		j;
	char	*new_str;

	i = -1;
	while ((*spl)[++i])
	{
		j = -1;
		while ((*spl)[i][++j])
		{
			if ((*spl)[i][j] == '$' && (*spl)[i][j + 1] == '(' && \
				in_quote((*spl)[i], j) != 1)
			{
				new_str = replace_split(d, (*spl)[i], j);
				if (new_str)
					setstr(d, &(*spl)[i--], new_str);
			}
		}
	}
}
