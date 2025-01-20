/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:31:42 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/14 22:50:13 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ls(t_data *d)
{
	struct dirent	*entry;
	DIR				*directory;
	(void)d;

	directory = opendir(d->cwd);
	if (directory == NULL)
		return (0);
	entry = readdir(directory);
	while (entry != NULL)
	{
		printf("%s	", entry->d_name);
		entry = readdir(directory);
	}
	printf("\n");
	closedir(directory);
	return (1);
}
