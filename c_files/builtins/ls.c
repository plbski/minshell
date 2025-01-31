/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:31:42 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/30 20:41:23 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

DIR	*get_directory(t_data *d, char *arg)
{
	DIR		*directory;
	char	*dir_path;

	if (arg)
		dir_path = ft_str_mega_join(d->cwd, "/", arg, NULL);
	else
		dir_path = ft_strdup(d->cwd);
	if (!dir_path)
		custom_exit(d, "Dir alloc in ls", NULL, EXIT_FAILURE);
	directory = opendir(dir_path);
	if (directory || !arg)
		return (directory);
	free(dir_path);
	dir_path = ft_strdup(arg);
	if (!dir_path)
		custom_exit(d, "Dir alloc in ls", NULL, EXIT_FAILURE);
	directory = opendir(dir_path);
	free(dir_path);
	return (directory);
}

void	display_entry(struct dirent *entry, int *len)
{
	if (entry->d_name[0] == '.')
		return ;
	printf("%-30s", entry->d_name);
	if ((*len)++ > 2)
	{
		printf("\n");
		*len = 0;
	}
}

int	execute_ls(t_data *d, char *arg, int print_arg)
{
	struct dirent	*entry;
	DIR				*directory;
	int				len;

	directory = get_directory(d, arg);
	if (!directory)
		return (printf("ls: %s: No such file or directory\n", arg), FCT_FAIL);
	entry = readdir(directory);
	if (!entry)
		return (FCT_FAIL);
	if (print_arg)
		printf("%s:\n", arg);
	len = 0;
	while (entry != NULL)
	{
		display_entry(entry, &len);
		entry = readdir(directory);
	}
	if (len != 0)
		printf("\n");
	return (closedir(directory), FCT_SUCCESS);
}

int	ls(t_data *d, char *arg, char **flags, int status)
{
	int	i;
	int	fct_ret;

	(void)status;
	fct_ret = execute_ls(d, arg, flags && flags[0]);
	if (!flags)
		return (fct_ret);
	i = -1;
	while (flags[++i])
	{
		if (execute_ls(d, flags[i], 1) == FCT_SUCCESS)
			fct_ret = FCT_SUCCESS;
	}
	return (fct_ret);
}
