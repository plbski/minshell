/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:31:42 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/26 18:13:45 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	ls(t_data *d _UNUSED, char *arg _UNUSED, char **flags, int status _UNUSED)
{
	char			*dir;
	struct dirent	*entry;
	DIR				*directory;
	int				len;

	if (flags && flags[0])
		return (printf("ls: too many arguments\n"), 0);
	if (arg)
		dir = ft_str_mega_join(d->cwd, "/", arg, NULL);
	else
		dir = ft_strdup(d->cwd);
	if (!dir)
		custom_exit(d, "Dir alloc in ls", NULL, EXIT_FAILURE);
	printf("%s\n", dir);
	directory = opendir(dir);
	free(dir);
	if (directory == NULL)
		return (0);
	entry = readdir(directory);
	len = 0;
	while (entry != NULL)
	{
		printf("%-30s", entry->d_name);
		entry = readdir(directory);
		if (len++ > 2)
		{
			printf("\n");
			len = 0;
		}
	}
	return (printf("\n"), closedir(directory), 1);
}
