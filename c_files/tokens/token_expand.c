/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:21:54 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/03/04 13:23:23 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

char	*expand_special_segment(t_data *d, char *split, int *i)
{
	char	*str;

	str = NULL;
	if (split[*i + 1] == '$')
		str = ft_itoa(getpid());
	else if (split[*i + 1] == '?')
		str = ft_itoa(d->last_exit);
	else if (split[*i + 1] == '0')
		str = ft_strjoin(d->msh_wd, "/minishell");
	else if (split[*i + 1] == '\"' || !split[*i + 1])
		str = ft_strdup("$");
	else if (ft_isdigit(split[*i + 1]) && split[*i + 2])
	{
		str = ft_strdup(split + *i + 2);
		(*i) += ft_strlen(split + *i + 1);
	}
	else
		return (NULL);
	if (!str)
		custom_exit(d, "alloc for $", NULL, EXIT_FAILURE);
	(*i)++;
	return (str);
}

char	*expand_segment(t_data *d, char *split, int *i)
{
	int		start;
	char	*var_name;
	char	*value;
	char	*spc_str;

	spc_str = expand_special_segment(d, split, i);
	if (spc_str)
		return (spc_str);
	(*i)++;
	start = *i;
	while (split[*i] && (ft_isalnum(split[*i]) || split[*i] == '_'))
		(*i)++;
	var_name = copy_until_char(d, split, &start, "$?'\"./");
	if (!var_name)
		return (split);
	value = get_env_value(d, d->env_list, var_name);
	if (!value)
		value = get_env_value(d, d->var_list, var_name);
	free(var_name);
	(*i)--;
	return (value);
}

char	*expand_split(t_data *d, char *split, int len, int i)
{
	char	**spl_values;
	char	*new_str;
	int		spl_index;

	spl_index = 0;
	spl_values = ms_malloc(d, sizeof(char *) * (len + 1));
	while (i < (len + 1) && split[i])
	{
		if (split[i] == '$' && in_quote(split, i) != 1)
		{
			new_str = expand_segment(d, split, &i);
			if (new_str)
				spl_values[spl_index++] = new_str;
		}
		else if (split[i] == '$')
			spl_values[spl_index++] = copy_until_char(d, split, &i, "\'");
		else
			spl_values[spl_index++] = copy_until_char(d, split, &i, "$");
		i++;
	}
	spl_values[spl_index] = NULL;
	new_str = contract_str(d, spl_values);
	return (free_void_array((void ***)&spl_values), new_str);
}

t_token	*update_node_expansion(t_data *d, t_token *node)
{
	char	*new_name;

	node = swap_redir_cmd(d, node);
	if (node->type == tk_cmd)
		set_redir_arg(node);
	new_name = NULL;
	if (!node->name)
		node->name = ms_strdup(d, "");
	if (!node->name[0])
		return (node);
	if (node->name[0] == '~' && (!node->name[1] || node->name[1] == '/') && \
		d->home_wd[0] != '?')
		replace_strstr(d, &node->name, "~", d->home_wd);
	if (chr_amnt(node->name, '$', 0))
	{
		new_name = expand_split(d, node->name, ft_strlen(node->name), 0);
		if (new_name && node->type == tk_cmd && chr_amnt(new_name, ' ', 0))
			node = insert_expanded_tokens(d, node, new_name);
		else
			setstr(d, &node->name, new_name);
	}
	remove_quotes(d, &node->name);
	return (node);
}
