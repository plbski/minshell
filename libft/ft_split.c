/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:16:33 by gvalente          #+#    #+#             */
/*   Updated: 2024/10/23 14:05:13 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_str_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static int	get_next_size(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

static char	*free_split(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return NULL;
}

static char	**get_splits(char const *s, char c, char **strs, int count)
{
	int	i;
	int	u;

	u = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		strs[count] = malloc(get_next_size(s, c, i) + 1);
		if (!strs[count])
		{
			free_split(strs, count);
			return (NULL);
		}
		u = 0;
		while (s[i] && s[i] != c)
			strs[count][u++] = s[i++];
		strs[count][u] = '\0';
		count++;
	}
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		str_count;

	if (!s)
		return (NULL);
	str_count = get_str_count(s, c);
	strs = (char **)malloc((str_count + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	strs[str_count] = NULL;
	return (get_splits(s, c, strs, 0));
}
