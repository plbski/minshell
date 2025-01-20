/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:16:19 by gvalente          #+#    #+#             */
/*   Updated: 2024/10/03 18:40:12 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(char const *s1, char const *set)
{
	int	start;
	int	end;

	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1) - 1;
	while (end >= start && ft_strchr(set, s1[end]))
		end--;
	return (end - start + 1);
}

static char	*trim(char const *s1, int trim_size, char const *set)
{
	int		start;
	int		end;
	char	*trimmed;

	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1) - 1;
	while (end >= start && ft_strchr(set, s1[end]))
		end--;
	trimmed = malloc(trim_size + 1);
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, &s1[start], trim_size + 1);
	return (trimmed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	new_size;

	if (!s1 || !set)
		return (NULL);
	new_size = get_size(s1, set);
	if (new_size <= 0)
		return (ft_strdup(""));
	return (trim(s1, new_size, set));
}
