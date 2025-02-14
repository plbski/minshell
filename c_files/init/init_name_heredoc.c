/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_name_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:01:03 by pbuet             #+#    #+#             */
/*   Updated: 2025/02/14 16:24:53 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void name_heredoc(t_data d)
{
	int		i;
	int 	j;
	int		len;
	char	*base = "0123456789ABCDEF";
	char	*result;

	j = 0;
	i = 1024;
	len = ft_strlen(d.cwd);
	result = malloc(9);
	while (i > 16)
	{
		result[j] = base[i % 16];
		i = i / 16;
		j ++;
	}
	result = ft_str_mega_join(d.cwd, "/", result, NULL);
	printf("%s\n", result);
}