/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strinsert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:19:24 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/19 21:21:01 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../msh.h"

char	*ms_strndup(t_data *d, const char	*s1, ssize_t n)
{
	char		*dst;
	ssize_t		i;
	ssize_t		len;

	if (!s1 || n < 0)
		return (NULL);
	len = ft_strlen(s1);
	if (n > len)
		n = len;
	dst = (char *)malloc(n + 1);
	if (!dst)
		custom_exit(d, "strndup alloc fail", NULL, EXIT_FAILURE);
	i = 0;
	while (i < n)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strndup(const char	*s1, ssize_t n)
{
	char		*dst;
	ssize_t		i;
	ssize_t		len;

	if (!s1 || n < 0)
		return (NULL);
	len = ft_strlen(s1);
	if (n > len)
		n = len;
	dst = (char *)malloc(n + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	replace_strstr(t_data *d, char **str, \
	const char *remove, const char *replace)
{
	char	*new_str;
	int		i;
	int		j;

	if (!str || !*str || !(*str)[0] || !remove || !ft_strstr(*str, remove))
		return ;
	i = -1;
	while ((*str)[++i])
	{
		j = 0;
		while (remove[j] && remove[j] == (*str)[i + j])
			j++;
		if (remove[j])
			continue ;
		new_str = ms_strdup(d, (*str) + i + j);
		setstr(d, str, ms_strjoin(d, replace, new_str));
		free(new_str);
		return ;
	}
	return ;
}

char	*str_insert(const char *str, int rmv_start, \
int rmv_end, const char *new_str)
{
	char	*head;
	char	*tail;
	char	*result;
	int		len;

	if (!str || !new_str || rmv_start > rmv_end || rmv_start < 0)
		return (NULL);
	len = ft_strlen(str);
	if (rmv_end >= len)
		return (NULL);
	head = ft_strndup(str, rmv_start);
	if (!head)
		return (ft_dprintf(2, "alloc fail str_insert"), NULL);
	tail = ft_strdup(str + rmv_end + 1);
	if (!tail)
		return (free(head), ft_dprintf(2, "alloc fail str_insert"), NULL);
	result = ft_megajoin(head, new_str, tail, NULL);
	free(head);
	free(tail);
	if (!result)
		return (ft_dprintf(2, "alloc fail str_insert"), NULL);
	return (result);
}
