/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:50:03 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/28 22:42:33 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	write_anim_txt(t_data *d, const char *txt, int intrv, int exit_w)
{
	int		i;
	char	*string;
	char	*lvl_str;

	lvl_str = ft_itoa(d->shlvl);
	if (!lvl_str)
		custom_exit(d, "Alloc fail for shlvl in anim", NULL, EXIT_FAILURE);
	string = ft_str_mega_join(txt, MAGENTA, lvl_str, RESET);
	free(lvl_str);
	if (!string)
		custom_exit(d, "Alloc fail for string in anim", NULL, EXIT_FAILURE);
	printf(RED);
	i = -1;
	while (string[++i])
	{
		usleep(intrv);
		printf("%c", string[i]);
		fflush(stdout);
	}
	printf("\n");
	printf(RESET);
	return (usleep(exit_w), free(string), 1);
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

char	*get_prompt_message(t_data *d)
{
	char	*logname_part;
	char	*cwd_part;
	char	*prompt_msg;
	char	*icon_part;

	logname_part = ft_str_mega_join(PROMPT_LOGNAME_COL, d->logname, " ", RESET);
	if (!logname_part)
		return (NULL);
	icon_part = ft_str_mega_join(MAGENTA, "$ ", RESET, NULL);
	cwd_part = ft_str_mega_join(PROMPT_CWD_COL, d->cwd, icon_part, RESET);
	prompt_msg = ft_strjoin(logname_part, cwd_part);
	free(icon_part);
	free(cwd_part);
	free(logname_part);
	return (prompt_msg);
}
