/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:09:44 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/23 03:57:35 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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

void	export(t_data *d, char *prompt)
{
	char		*trimmed_prompt;
	char		*key;
	t_dblist	*new_node;
	t_dblist	*element;

	if (!ft_strncmp(prompt, "export", 7))
		return (reorder_dblst(dblst_first(d->env_list)), print_env(d));
	trimmed_prompt = ft_remove_prefix(prompt, "export ");
	if (!trimmed_prompt)
		custom_exit(d, 0);
	key = truncate_at_end(trimmed_prompt, '=');
	if (!key)
		return ;
	element = get_dblst_at_key(d->env_list, key);
	if (element)
	{
		free(element->content);
		element->content = trimmed_prompt;
		update_env_variables(d);
		update_environ(d);
		return ;
	}
	new_node = dblst_new(trimmed_prompt);
	dblst_add_back(&d->env_list, new_node);
	update_environ(d);
}

void	unset(t_data *d, char *prompt)
{
	char		*key;
	t_dblist	*element;

	if (!prompt)
		return ;
	key = ft_remove_prefix(prompt, "unset ");
	if (!key)
		return ;
	element = get_dblst_at_key(d->env_list, key);
	if (!element)
		return ;
	dblst_delone(element, free);
}


// t_key_value	*init_key_value(char *text)
// {
// 	char		**split;
// 	t_key_value	*key_value;

// 	if (!text)
// 		return (NULL);
// 	key_value = malloc(sizeof(t_key_value));
// 	if (!key_value)
// 		return (NULL);
// 	split = ft_split(text, "=");
// 	if (!split)
// 		return (NULL);
// 	key_value->key = split[0];
// 	key_value->value = split[1];
// 	free(split);
// 	return (key_value);
// }
