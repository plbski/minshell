/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:04:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/14 04:03:30 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	g_quit_in_heredoc;

char	*get_last_line(t_data *d, const char *filename)
{
	int		fd;
	char	*line;
	char	*last_line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	last_line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		safe_free(last_line);
		last_line = ms_strdup(d, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (last_line);
}

int	main(int argc, char *argv[], char **env)
{
	t_data	data;

	(void)argv;
	data.debug_mode = argc > 1;
	setup_signal(0, 0);
	init_data(&data, env);
	data.prv_input = get_last_line(&data, data.history_wd);
	if (data.prv_input)
		data.prv_input[ft_strlen(data.prv_input) - 1] = '\0';
	printf("%s lv %d\n", START_ANIM_TEXT, data.shlvl);
	while (42)
	{
		if (!process_input(&data))
			break ;
	}
	custom_exit(&data, NULL, NULL, EXIT_SUCCESS);
	return (0);
}
