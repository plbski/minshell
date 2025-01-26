/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:29:00 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/26 14:41:24 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

/**
 * @note 
 * @attention 
 * @todo 
 */
int	handle_splits(t_data *d, char *prompt)
{
	char	**splits;
	int		i;

	(void)d;
	splits = ft_split_str(prompt, "&&");
	if (!splits)
		return (0);
	i = -1;
	while (splits[++i])
		execute_prompt(d, splits[i]);
	free(splits);
	return (1);
}

void	expand_splits_values(t_data *d, char **splits)
{
	int	i;

	i = -1;
	while (splits[++i])
	{
		if (splits[i][0] == '$')
		{
			free(splits[i]);
			splits[i] = get_env_value(d, splits[i] + 1);
		}
	}
}

char	**get_splits(t_data *d, char *prmpt, char **cmd_name, char **arg)
{
	char	**splits;

	splits = ft_split(prmpt, ' ');
	if (!splits)
		custom_exit(d, "Alloc failed for tokens", NULL, EXIT_FAILURE);
	expand_splits_values(d, splits);
	*cmd_name = ft_strdup(splits[0]);
	if (!*cmd_name)
	{
		free_void_array((void ***)&splits);
		custom_exit(d, "Alloc failed for arg", NULL, EXIT_FAILURE);
	}
	if (splits[1])
	{
		*arg = ft_strdup(splits[1]);
		if (!*arg)
		{
			free_void_array((void ***)&splits);
			custom_exit(d, "Alloc failed for arg", NULL, EXIT_FAILURE);
		}
	}
	return (splits);
}

char	**init_flags(t_data *d, int splits_amount, char **splits)
{
	int		i;
	char	**flags;

	flags = malloc(sizeof(char *) * (splits_amount - 1));
	if (!flags)
	{
		free_void_array((void ***)&splits);
		custom_exit(d, "Alloc failed for flags", NULL, EXIT_FAILURE);
	}
	i = 1;
	while (splits[++i])
	{
		flags[i - 2] = ft_strdup(splits[i]);
		if (!flags[i - 2])
		{
			free_void_array((void ***)&flags);
			free_void_array((void ***)&splits);
			custom_exit(d, "Alloc failed for token", NULL, EXIT_FAILURE);
		}
	}
	flags[i - 2] = NULL;
	return (flags);
}

char	**get_flags(t_data *d, char *prmpt, char **cmd_name, char **arg)
{
	char	**splits;
	char	**flags;
	int		splits_len;

	splits = get_splits(d, prmpt, cmd_name, arg);
	splits_len = get_arr_len((void **)splits);
	if (splits_len - 1 <= 0)
		return (NULL);
	flags = init_flags(d, splits_len, splits);
	free_void_array((void ***)&splits);
	// printf("cmd: %s arg: %s\n", *cmd_name, *arg);
	// for (int i = 0; flags && flags[i]; i++)
	// 	printf("flag[%d] > %s\n", i, flags[i]);
	// exit (0);
	return (flags);
}
