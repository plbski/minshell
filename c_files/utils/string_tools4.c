/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tools4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 04:35:39 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/13 18:48:06 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	const char	*cur_str;
	const char	*cur_to_find;

	if (!*to_find)
		return ((char *)str);
	while (*str)
	{
		cur_str = str;
		cur_to_find = to_find;
		while (*cur_str == *cur_to_find && *cur_to_find)
		{
			cur_str++;
			cur_to_find++;
		}
		if (!*cur_to_find)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

// Count substrings split by 'sep'
static int	count_substrings(char *str, char *sep)
{
	int			count;
	char		*next;

	count = 0;
	if (!str || !sep || !*sep)
		return (0);
	next = ft_strstr(str, sep);
	while (next)
	{
		count++;
		str = next + ft_strlen(sep);
		next = ft_strstr(str, sep);
	}
	return (count + 1);
}

// Get the next segment between separators
static char	*get_next_segment(t_data *d, char **str, char *sep)
{
	char	*next;
	char	*segment;
	size_t	len;

	if (!*str)
		return (NULL);
	next = ft_strstr(*str, sep);
	if (!next)
	{
		segment = ms_strdup(d, *str);
		*str = NULL;
		return (segment);
	}
	len = next - *str;
	segment = malloc(len + 1);
	if (!segment)
		return (NULL);
	ft_strlcpy(segment, *str, len);
	segment[len] = '\0';
	*str = next + ft_strlen(sep);
	return (segment);
}

char	**ft_split_str(t_data *d, char *str, char *sep)
{
	char	**splits;
	int		amount;
	int		i;

	if (!str || !sep || !*sep)
		return (NULL);
	amount = count_substrings(str, sep);
	splits = malloc(sizeof(char *) * (amount + 1));
	if (!splits)
		return (NULL);
	i = -1;
	while (++i < amount)
	{
		splits[i] = get_next_segment(d, &str, sep);
		if (splits[i] && *splits[i] != '\0')
		{
			splits[i] = ft_strtrim(splits[i], " ");
			if (!splits[i])
				return (free_void_array((void ***)&splits), NULL);
		}
		else
			free(splits[i]);
	}
	return (splits[i] = NULL, splits);
}

int	char_in_str(char c, const char *txt)
{
	int	i;

	i = -1;
	while (txt[++i])
	{
		if (txt[i] == c)
			return (1);
	}
	return (0);
}
