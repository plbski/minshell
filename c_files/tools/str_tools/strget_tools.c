/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strget_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:03:05 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/14 04:23:28 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

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

char	*char_join(char a, char b, char c, char d)
{
	const char	chars[] = {a, b, c, d};
	char		*str;
	int			len;
	int			i;

	len = 0;
	i = -1;
	while (++i < 4)
		if (chars[i])
			len++;
	if (!len)
		return (NULL);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	len = 0;
	i = -1;
	while (++i < 4)
		if (chars[i])
			str[len++] = chars[i];
	str[len] = '\0';
	return (str);
}

char	*replace_str(t_data *d, char *str, char *remove, char *replace)
{
	char	*new_str;
	int		i;
	int		j;
	char	*joined;

	if (!str || !remove)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		j = 0;
		while (remove[j] && remove[j] == str[i + j])
			j++;
		if (remove[j])
			continue ;
		new_str = ms_strdup(d, str + i + j);
		joined = ms_strjoin(d, replace, new_str);
		free(new_str);
		return (joined);
	}
	return (ms_strdup(d, str));
}
