/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:27:21 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/13 22:05:54 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

t_dblist	*get_dblst_node(t_dblist *lst, const char *content)
{
	t_dblist	*first_node;

	if (!lst)
		return (NULL);
	first_node = dblst_first(lst);
	if (cmp_str(first_node->content, content))
		return (first_node);
	lst = first_node->next;
	while (lst && lst != first_node)
	{
		if (cmp_str(lst->content, content))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

char	**get_base_env(t_data *d)
{
	char	**base_env;
	char	*pwd;
	char	*pwd_path;

	base_env = malloc(sizeof(char *) * 6);
	base_env[0] = ms_strdup(d, "SHLVL=1");
	base_env[1] = ms_strdup(d, "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/\
			usr/bin:.:/.local/opt/go/bin:/go/bin");
	base_env[2] = ms_strdup(d, "_=/usr/bin/env");
	pwd = ms_strdup(d, "PWD=");
	pwd_path = custom_get_cwd(d);
	base_env[3] = ms_strjoin(d, pwd, pwd_path);
	free(pwd);
	free(pwd_path);
	base_env[4] = getenv("LOGNAME");
	base_env[5] = NULL;
	return (base_env);
}

void	init_env_list(t_data *d, char **env)
{
	char	**base_env;

	d->received_env = (env && env[0]);
	if (!d->received_env)
		base_env = get_base_env(d);
	if (d->env_list)
		dblst_clear(&d->env_list, free);
	if (d->received_env)
	{
		d->tmp_list = arr_to_dblst((void **)env);
		d->env_list = arr_to_dblst((void **)env);
	}
	else
	{
		d->env_list = arr_to_dblst((void **)base_env);
		d->tmp_list = arr_to_dblst((void **)base_env);
		free_void_array((void ***)&base_env);
	}
	if (!d->env_list)
		custom_exit(d, "List alloc failed", NULL, 1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (unsigned char)(*s1) - (unsigned char)(*s2);
}

void	reorder_dblst(t_dblist *list)
{
	t_dblist	*db_b;
	char		*tmp;

	while (list)
	{
		db_b = list->next;
		while (db_b)
		{
			if (list->content && db_b->content && \
				ft_strcmp((char *)list->content, (char *)db_b->content) > 0)
			{
				tmp = list->content;
				list->content = db_b->content;
				db_b->content = tmp;
			}
			db_b = db_b->next;
		}
		list = list->next;
	}
}
