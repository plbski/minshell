/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:50:03 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/31 18:56:26 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

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

void	replace_rline(void)
{
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line ();
	rl_redisplay();
}
