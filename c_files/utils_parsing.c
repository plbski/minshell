/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:46:58 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/22 20:43:37 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*ft_remove_prefix(char *str, char *prefix, int space)
{
	size_t	prefix_len;

	if (!str || !prefix)
		return (NULL);
	prefix_len = ft_strlen(prefix);
	if (ft_strncmp(str, prefix, prefix_len) == 0)
	{
		if (space == 1)
		{
			while(str[prefix_len] == 32)
			prefix_len ++;
		}
		return (ft_strdup(str + prefix_len));
	}
	return (ft_strdup(str));
}

char	*truncate_at_end(char *str, char cut_letter)
{
	char	*trunc_str;
	int		i;
	int		trunc_index;

	if (!str)
		return (NULL);
	i = ft_strlen(str) - 1;
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
	i = -1;
	while (++i < trunc_index)
		trunc_str[i] = str[i];
	trunc_str[i] = '\0';
	return (trunc_str);
}

char	*get_array_element_with_prefix(char **array, \
	char *prefix)
{
	int		i;
	int		j;

	if (!array || !prefix)
		return (NULL);
	i = 0;
	while (array[i] != NULL)
	{
		j = 0;
		while (array[i][j] == prefix[j])
			j++;
		if (!prefix[j])
			return (array[i]);
		i++;
	}
	return (NULL);
}

char	*ft_str_mega_join(char *a, char *b, char *c, char *d)
{
	char	*ab;
	char	*abc;
	char	*abcd;

	if (a == NULL || b == NULL)
		return (NULL);
	ab = ft_strjoin(a, b);
	if (!ab)
		return (NULL);
	if (c == NULL)
		return (ab);
	abc = ft_strjoin(ab, c);
	free(ab);
	if (!abc)
		return (NULL);
	if (!d)
		return (abc);
	abcd = ft_strjoin(abc, d);
	free(abc);
	if (!abcd)
		return (NULL);
	return (abcd);
}

int	get_char_occurence(char *str, char c)
{
	int	i;
	int	occurence;

	if (!str)
		return (0);
	occurence = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			occurence++;
	}
	return (occurence);
}
