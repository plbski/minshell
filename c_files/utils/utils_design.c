/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_design.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:50:03 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/24 15:07:58 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	write_animated_txt(char *txt_to_display, int interval, int exit_wait)
{
	int		i;
	char	*txt;

	txt = ft_strdup(txt_to_display);
	if (!txt)
		return (0);
	printf(RED);
	i = -1;
	while (txt[++i])
	{
		usleep(interval);
		printf("%c", txt[i]);
		fflush(stdout);
	}
	printf("\n");
	printf(RESET);
	return (usleep(exit_wait), free(txt), 1);
}

void	set_string_color(char **str, char *color)
{
	char	*new_str;

	if (!*str)
		return ;
	if (!color)
		return ;
	new_str = ft_str_mega_join(color, *str, RESET, NULL);
	free(*str);
	*str = new_str;
}
