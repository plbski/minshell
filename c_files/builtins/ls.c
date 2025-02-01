/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:31:42 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/31 20:53:23 by giuliovalen      ###   ########.fr       */
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
		dir_path = ms_strdup(d, d->cwd);
	if (!dir_path)
		custom_exit(d, "Dir alloc in ls", NULL, EXIT_FAILURE);
	directory = opendir(dir_path);
	if (directory || !arg)
		return (directory);
	free(dir_path);
	dir_path = ms_strdup(d, arg);
	directory = opendir(dir_path);
	free(dir_path);
	return (directory);
}

void	display_entry(struct dirent *entry, int *len)
{
	char	*color;

	color = RESET;
	if (entry->d_name[0] == '.')
		return ;
	if (is_directory(entry->d_name))
		color = BLUE;
	else if (ft_strstr(entry->d_name, ".a"))
		color = YELLOW;
	else if (ft_strstr(entry->d_name, ".h"))
		color = MAGENTA;
	else if (access(entry->d_name, X_OK) != -1)
		color = RED;
	printf("%s%-30s%s", color, entry->d_name, RESET);
	if ((*len)++ > 2)
	{
		printf("\n");
		*len = 0;
	}
}

int	execute_ls(t_data *d, char *arg, int print_arg, int error_if_dir)
{
	struct dirent	*entry;
	DIR				*directory;
	int				len;

	directory = get_directory(d, arg);
	if (!directory)
	{
		if (error_if_dir)
			printf("ls: %s: No such file or directory\n", arg);
		return (FCT_FAIL);
	}
	entry = readdir(directory);
	if (!entry)
		return (FCT_FAIL);
	if (print_arg)
		printf("%s%s:\n%s", GREEN, arg, RESET);
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
	fct_ret = execute_ls(d, arg, flags && flags[0], 1);
	if (!flags)
		return (fct_ret);
	i = -1;
	while (flags[++i])
	{
		if (execute_ls(d, flags[i], 1, 0) == FCT_SUCCESS)
		{
			fct_ret = FCT_SUCCESS;
			if (flags[i + 1] && is_directory(flags[i + 1]))
				printf("\n");
		}
	}
	return (fct_ret);
}
