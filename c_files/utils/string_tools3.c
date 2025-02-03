/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tools3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:03:05 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/03 13:10:54 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	*ms_strjoin(t_data *d, char const *s1, char const *s2)
{
	int		i;
	int		u;
	char	*joined;

	if (!s1)
		return (NULL);
	if (!s2)
		return (ms_strdup(d, s1));
	joined = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined)
	{
		printf("%s - %s > ", s1, s2);
		custom_exit(d, "alloc failed in strjoin", NULL, EXIT_FAILURE);
	}
	i = -1;
	while (s1[++i])
		joined[i] = s1[i];
	u = -1;
	while (s2[++u])
		joined[i + u] = s2[u];
	joined[i + u] = '\0';
	return (joined);
}

char	*ms_strdup(t_data *d, const char	*s1)
{
	char	*dst;
	int		i;
	int		len;

	len = ft_strlen(s1);
	dst = (char *)malloc(len + 1);
	if (!dst)
	{
		printf("%s > ", s1);
		custom_exit(d, "alloc failed in strdup", NULL, EXIT_FAILURE);
	}
	i = 0;
	while (i < len)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	*ms_malloc(t_data *d, ssize_t size)
{
	void	*content;

	content = malloc(size);
	if (!content)
		custom_exit(d, "malloc failed", NULL, EXIT_FAILURE);
	return (content);
}

int	is_all_digit(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

int	get_char_index(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}
