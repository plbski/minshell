/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:31:42 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/24 18:42:14 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	ls(t_data *d, char *arg, char *flags, int status)
{
	struct dirent	*entry;
	DIR				*directory;
	int				len;

	(void)d;
	(void)status;
	if (arg || flags)
		return (printf("ls: too many arguments\n"), 0);
	directory = opendir(d->cwd);
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
	printf("\n");
	closedir(directory);
	return (1);
}
