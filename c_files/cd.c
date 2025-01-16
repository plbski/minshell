/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:29:41 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/14 23:37:42 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void cd(t_data *d, char *prompt)
{
    char    *prompt_path;

    prompt_path = ft_remove_prefix(prompt, "cd ");
    if (chdir(prompt_path) == -1)
        printf("%s", "wrong path\n");
    update_cwd(d);
    free(prompt_path);
}
