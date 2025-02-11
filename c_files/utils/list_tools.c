/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:27:21 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/11 09:18:57 by giuliovalen      ###   ########.fr       */
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

void	add_to_list(t_data *d, t_dblist *lst, char *content)
{
	t_dblist	*new_node;
	char		*new_content;

	if (!content)
		custom_exit(d, "no content for new list node", NULL, EXIT_FAILURE);
	new_content = ms_strdup(d, content);
	new_node = dblst_new(new_content);
	dblst_add_back(&lst, new_node);
}

void	init_with_empty_env(t_data *d)
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
	init_env_list(d, base_env);
	free_void_array((void ***)&base_env);
}

void	init_env_list(t_data *d, char **env)
{
	if (!env || !env[0])
		init_with_empty_env(d);
	if (d->env_list)
		dblst_clear(&d->env_list, free);
	d->env_list = arr_to_dblst((void **)env);
	if (!d->env_list)
		custom_exit(d, "List alloc failed", NULL, 1);
}

void	reorder_dblst(t_dblist *list)
{
	t_dblist	*db_b;
	char		*tmp;
	int			min_len;

	while (list->next)
	{
		db_b = list->next;
		while (db_b->next)
		{
			if (!list->content || !db_b->content)
				continue ;
			min_len = ft_strlen((char *)list->content);
			if (min_len > ft_strlen((char *)db_b->content))
				min_len = ft_strlen((char *)db_b->content);
			if (ft_strncmp((char *)list->content, (char *)db_b->content, \
				min_len) > 0)
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
