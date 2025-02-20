/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:50:03 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/19 23:49:32 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../msh.h"

void	ms_substr(t_data *d, char **s, unsigned int start, size_t len)
{
	char	*new_str;

	if (!s)
		return ;
	new_str = ft_substr(*s, start, len);
	if (!new_str)
		custom_exit(d, "error in substr\n", NULL, EXIT_FAILURE);
	free(*s);
	*s = new_str;
}

void	reset_readline(void)
{
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line ();
	rl_redisplay();
}

int	is_directory(const char *path)
{
	struct stat	entry_stat;

	if (stat(path, &entry_stat) == 0)
		return ((entry_stat.st_mode & S_IFMT) == S_IFDIR);
	return (0);
}

void	setstr(t_data *d, char **str, char *new)
{
	(void)d;
	safe_free(*str);
	*str = new;
}

char	**ms_split(t_data *d, const char *str, char remove)
{
	char	**splits;

	if (!str)
		return (NULL);
	splits = ft_split(str, remove);
	if (!splits)
	{
		ft_dprintf(2, "%s split failed\n", str);
		custom_exit(d, NULL, NULL, EXIT_FAILURE);
	}
	return (splits);
}
