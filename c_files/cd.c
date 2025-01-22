/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:29:41 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/22 19:29:25 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	cd(t_data *d, char *prompt)
{
	char	*prompt_path;

	prompt_path = ft_remove_prefix(prompt, "cd ", 1);
	if (!ft_strncmp(prompt_path, "~", 2) && d->home_wd != NULL)
	{
		free(prompt_path);
		prompt_path = ft_strdup(d->home_wd);
	}
	if (!ft_strncmp(prompt_path, "-", 2) && d->prev_cwd != NULL)
	{
		free(prompt_path);
		prompt_path = ft_strdup(d->prev_cwd);
	}
	if (chdir(prompt_path) == -1)
		printf("cd: no such file or directory: %s\n", prompt_path);
	update_cwd(d);
	free(prompt_path);
}

void	pwd(t_data *d)
{
	printf("%s\n", d->cwd);
}
