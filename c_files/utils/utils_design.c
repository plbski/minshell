/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_design.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:50:03 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/26 13:38:36 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	write_anim_txt(t_data *d, const char *txt, int intrv, int exit_w)
{
	int		i;
	char	*string;
	char	*lvl_str;

	lvl_str = get_env_value(d, "SHLVL");
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

int	is_same_string(char *a, char *b)
{
	int	len_a;
	int	len_b;
	int	i;

	len_a = ft_strlen(a);
	len_b = ft_strlen(b);

	if (len_a != len_b)
		return (0);
	i = -1;
	while (++i < len_a)
	{
		if (a[i] != b[i])
			return (0);
	}
	return (1);
}