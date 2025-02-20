/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strget_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:03:05 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/18 11:30:11 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../msh.h"

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

void	*ms_realloc(t_data *d, void *ptr, size_t new_size)
{
	void	*new_ptr;

	if (!ptr)
		return (ms_malloc(d, new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = ms_malloc(d, new_size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
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
