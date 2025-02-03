/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:27:32 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/03 11:46:56 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	exec_cat(t_data *d, char *file_name)
{
	char	*buffer;

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
	buffer = read_file(d, file_name);
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

	(void)status;
	if (!arg)
		return (FCT_FAIL);
	fct_ret = exec_cat(d, arg);
	i = -1;
	while (flags && flags[++i])
	{
		if (exec_cat(d, flags[i]) == FCT_SUCCESS)
			fct_ret = FCT_SUCCESS;
	}
	return (fct_ret);
}
