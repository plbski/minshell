/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:50:03 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/14 00:02:29 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\nMinishell$ ");
}

int	write_animated_txt(char *txt_to_display, int interval, int exit_wait)
{
	int		i;
	char	*txt;

	txt = ft_strdup(txt_to_display);
	if (!txt)
		return (0);
	printf(RED);
	printf("\n");
	i = -1;
	while (txt[++i])
	{
		usleep(interval);
		printf("%c", txt[i]);
		fflush(stdout);
	}
	printf("\n\n");
	printf(RESET);
	return (usleep(exit_wait), free(txt), 1);
}
