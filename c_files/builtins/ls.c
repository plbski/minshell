/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:31:42 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/24 13:56:27 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	ls(t_data *d, char *arg, char *flags, int status)
{
	struct dirent	*entry;
	DIR				*directory;

	(void)d;
	(void)arg;
	(void)flags;
	(void)status;
	directory = opendir(d->cwd);
	if (directory == NULL)
		return (0);
	entry = readdir(directory);
	while (entry != NULL)
	{
		printf("%-10s", entry->d_name);
		entry = readdir(directory);
		printf("\n");
	}
	printf("\n");
	closedir(directory);
	return (1);
}
