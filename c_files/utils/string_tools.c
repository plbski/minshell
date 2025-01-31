/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:46:58 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/31 14:17:30 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	*ft_remove_prefix(t_data *d, const char *str, char *prefix)
{
	size_t	prefix_len;

	if (!str || !prefix)
		return (NULL);
	prefix_len = ft_strlen(prefix);
	if (ft_strncmp(str, prefix, prefix_len) == 0)
		return (ms_strdup(d, str + prefix_len));
	return (ms_strdup(d, str));
}

char	*truncate_at_end(const char *str, char cut_letter)
{
	char	*trunc_str;
	int		i;
	int		trunc_index;

	if (!str || !chr_amnt(str, cut_letter))
		return (NULL);
	i = ft_strlen(str);
	while (--i >= 0)
		if (str[i] == cut_letter)
			break ;
	if (i <= 0)
		return (NULL);
	trunc_index = i;
	trunc_str = malloc(trunc_index + 1);
	if (!trunc_str)
		return (NULL);
	i = -1;
	while (++i < trunc_index)
		trunc_str[i] = str[i];
	return (trunc_str[i] = '\0', trunc_str);
}

char	*ft_str_mega_join(const char *a, const char *b, \
	const char *c, const char *d)
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

int	chr_amnt(const char *str, char c)
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

int	get_arr_len(void **arr)
{
	int	len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}
