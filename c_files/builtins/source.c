/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:50:51 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/21 14:56:30 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

char	*get_rc_path(t_data *d)
{
	return (ms_strjoin(d, d->start_wd, "/.mshrc"));
}

static int	exec_source(t_data *d, char *arg)
{
	char	*line;
	int		ms_fd;

	ms_fd = open(arg, O_RDONLY);
	if (ms_fd < 0)
		return (FCT_FAIL);
	line = get_next_line(ms_fd);
	while (line)
	{
		if (line[0] == '#')
		{
			setstr(d, &line, get_next_line(ms_fd));
			continue ;
		}
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (line[0] && line[0] != '\n')
			exec_input(d, line);
		setstr(d, &line, get_next_line(ms_fd));
	}
	close(ms_fd);
	return (FCT_OK);
}

int	source(t_data *d, char *arg, char **flags, int status)
{
	int		ret_value;
	int		i;

	(void)status;
	if (!arg)
	{
		arg = get_rc_path(d);
		ret_value = exec_source(d, arg);
		free(arg);
		return (ret_value);
	}
	if (exec_source(d, arg) == FCT_FAIL)
		return (ft_dprintf(2, "msh: %s: No such \
file or directory\n", arg), FCT_FAIL);
	i = -1;
	while (flags && flags[++i])
	{
		if (exec_source(d, flags[i]) == FCT_FAIL)
		{
			ft_dprintf(2, "msh: %s: No such file or directory\n", flags[i]);
			return (FCT_FAIL);
		}
	}
	return (FCT_OK);
}
