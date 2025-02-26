/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:50:51 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/26 19:42:42 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

char	*get_rc_path(t_data *d)
{
	return (ms_strjoin(d, d->start_wd, "/ressources/.mshrc"));
}

int	execute_line(t_data *d, char *arg, int *ret_value, int index)
{
	char	*line;
	char	line_buff[4048];
	int		ms_fd;

	ms_fd = open(arg, O_RDONLY);
	if (ms_fd < 0)
		return (*ret_value = FCT_FAIL, 0);
	line = get_next_line(ms_fd);
	while (line && index-- >= 0)
		setstr(d, &line, get_next_line(ms_fd));
	close(ms_fd);
	if (!line)
		return (*ret_value = FCT_OK, 0);
	ft_strlcpy(line_buff, line, 4048);
	free(line);
	if (line_buff[0] == '#')
		return (1);
	if (ft_strlen(line_buff) > 0 && line_buff[ft_strlen(line_buff) - 1] == '\n')
		line_buff[ft_strlen(line_buff) - 1] = '\0';
	if (!line_buff[0] || line_buff[0] == '\n')
		return (1);
	return (*ret_value = exec_input(d, line_buff), 1);
}

static int	exec_source(t_data *d, char *arg, int free_arg)
{
	char	argos[4048];
	int		ret_value;
	int		index;

	index = 0;
	ret_value = FCT_OK;
	ft_strlcpy(argos, arg, 4048);
	if (free_arg)
		free(arg);
	while (execute_line(d, argos, &ret_value, index++))
		continue ;
	return (ret_value);
}

int	source(t_data *d, char *arg, char **flags, int free_arg)
{
	int		i;

	if (!arg)
		return (exec_source(d, get_rc_path(d), 1));
	if (exec_source(d, arg, free_arg) == FCT_FAIL)
		return (ft_dprintf(2, "msh: %s: No such \
file or directory\n", arg), FCT_FAIL);
	i = -1;
	while (flags && flags[++i])
	{
		if (exec_source(d, flags[i], free_arg) == FCT_FAIL)
		{
			ft_dprintf(2, "msh: %s: No such file or directory\n", flags[i]);
			return (FCT_FAIL);
		}
	}
	return (FCT_OK);
}
