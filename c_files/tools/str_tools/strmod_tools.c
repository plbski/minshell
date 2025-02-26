/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmod_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:46:58 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/20 23:30:21 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../msh.h"

char	*ms_rem_prefix(t_data *d, char **str, const char *prefix, int alloc)
{
	char	*removed;
	int		prfx_len;
	int		str_len;
	int		new_len;

	if (!*str || !prefix || same_str(*str, prefix))
		return (NULL);
	str_len = ft_strlen(*str);
	prfx_len = ft_strlen(prefix);
	if (prfx_len > str_len)
		return (NULL);
	new_len = 0;
	while (new_len < prfx_len && (*str)[new_len] == prefix[new_len])
		new_len++;
	if (new_len != prfx_len)
		return (NULL);
	removed = ms_strdup(d, *str + new_len);
	if (alloc)
		return (removed);
	setstr(d, str, removed);
	return (*str);
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

char	*ft_megajoin(const char *a, const char *b, \
	const char *c, const char *d)
{
	char	*ab;
	char	*abc;
	char	*abcd;

	if (!a || !b)
		return (NULL);
	ab = ft_strjoin(a, b);
	if (!ab)
		return (NULL);
	if (!c)
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

char	*copy_until_char(t_data *d, char *str, int *start, const char *set)
{
	char	*copy;
	int		i;
	int		j;
	int		stop_index;

	if (*start >= ft_strlen(str) || str[*start] == '\0')
		return (NULL);
	i = *start;
	while (str[i] && !char_in_str(str[i], set))
		i++;
	stop_index = i;
	copy = malloc(stop_index - *start + 1);
	if (!copy)
		custom_exit(d, "alloc fail in token copy", NULL, EXIT_FAILURE);
	i = *start;
	j = -1;
	while (++j < stop_index - *start)
		copy[j] = str[i + j];
	copy[stop_index - *start] = '\0';
	*start = stop_index - 1;
	return (copy);
}

void	remove_chars(t_data *d, char **txt, const char *to_remove)
{
	char	*new_str;
	int		new_len;
	int		i;
	int		j;

	new_len = 0;
	i = -1;
	while ((*txt)[++i])
		if (!char_in_str((*txt)[i], to_remove))
			new_len++;
	if (new_len == ft_strlen(*txt))
		return ;
	new_str = malloc(new_len + 1);
	if (!new_str)
		custom_exit(d, "alloc in remove chars", NULL, EXIT_FAILURE);
	j = -1;
	i = -1;
	while ((*txt)[++i])
		if (!char_in_str((*txt)[i], to_remove))
			new_str[++j] = (*txt)[i];
	new_str[++j] = '\0';
	free(*txt);
	*txt = new_str;
}
