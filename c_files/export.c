/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:09:44 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/22 17:13:22 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	export(t_data *d, char *prompt)
{
	char		*trimmed_prompt;
	char		*key;
	t_dblist	*new_node;
	t_dblist	*element;

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
