/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plbuet <plbuet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:27:32 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/06 17:35:51 by plbuet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	exec_cat(t_data *d, char *file_name)
{
	char	*buffer;
	int		fd;

	if (!file_name)
		return (FCT_FAIL);
	if (access(file_name, F_OK) == -1)
	{
		printf("cat: %s: No such file or directory", file_name);
		return (FCT_FAIL);
	}
	if (is_directory(file_name))
	{
		printf("cat: %s: Is a directory\n", file_name);
		return (FCT_FAIL);
	}
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		custom_exit(d, "error in cat", NULL, EXIT_FAILURE);
	buffer = read_file(d, fd);
	if (!buffer)
		return (FCT_FAIL);
	printf("%s\n", buffer);
	free(buffer);
	return (FCT_SUCCESS);
}

int	cat(t_data *d, char *arg, char **flags, int status)
{
	int	i;
	int	fct_ret;
	char	*buffer;
	(void)status;

	if (!arg)
	{
		while ((buffer = get_next_line(STDIN_FILENO)) != NULL)
		{
			printf("%s", buffer);
			free(buffer);
		}
		return (FCT_SUCCESS);
	}
	fct_ret = exec_cat(d, arg);
	i = -1;
	while (flags && flags[++i])
	{
		if (exec_cat(d, flags[i]) == FCT_SUCCESS)
			fct_ret = FCT_SUCCESS;
	}
	return (fct_ret);
}
