/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:27:21 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/27 15:27:55 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

t_dblist	*get_dblst_node(t_dblist *lst, const char *content)
{
	t_dblist	*first_node;

	if (!lst)
		return (NULL);
	first_node = dblst_first(lst);
	if (is_same_string(first_node->content, content))
		return (first_node);
	lst = first_node->next;
	while (lst && lst != first_node)
	{
		if (is_same_string(lst->content, content))
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
	new_content = ft_strdup(content);
	if (!new_content)
		custom_exit(d, "alloc for content", NULL, EXIT_FAILURE);
	new_node = dblst_new(new_content);
	dblst_add_back(&lst, new_node);
}

void	init_env_list(t_data *d, char **env)
{
	if (d->env_list)
		dblst_clear(&d->env_list, free);
	d->env_list = arr_to_dblst((void **)env);
	if (!d->env_list)
		custom_exit(d, "List alloc failed", NULL, 1);
}
