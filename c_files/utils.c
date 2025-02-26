/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:50:03 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/20 17:29:09 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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

char	*ft_remove_prefix(char *str, char *prefix)
{
	size_t	prefix_len;

	if (!str || !prefix)
		return (NULL);
	prefix_len = ft_strlen(prefix);
	if (ft_strncmp(str, prefix, prefix_len) == 0)
		return (ft_strdup(str + prefix_len));
	return (ft_strdup(str));
}

char	*truncate_at_end(char *str, char cut_letter)
{
	char	*trunc_str;
	int		i;
	int		trunc_index;
	int		str_len;

	if (!str)
		return (NULL);
	str_len = ft_strlen(str);
	i = str_len - 1;
	while (i >= 0)
	{
		if (str[i] == cut_letter)
			break ;
		i--;
	}
	if (i < 0)
		return (ft_strdup(str));
	trunc_index = i;
	trunc_str = malloc(trunc_index + 1);
	if (!trunc_str)
		return (NULL);
	i = 0;
	while (i++ < trunc_index)
		trunc_str[i] = str[i];
	trunc_str[i] = '\0';
	return (trunc_str);
}

int	create_file(t_data *d, char *content, char *file_name)
{
	char	*full_path;
	int		fd;

	printf("CREATING FILE\n");
	full_path = ft_strjoin(d->cwd, file_name);
	printf("%s\n", full_path);
	fd = open(full_path, O_CREAT, O_TRUNC, 0644);
	if (fd == -1)
		return (0);
	write(fd, content, ft_strlen(content));
	return (1);
}
