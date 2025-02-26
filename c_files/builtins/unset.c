/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:26:40 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/25 22:53:10 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static int	is_valid_identifier(char *arg)
{
	int	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 0;
	while (arg[++i])
	{
		if (!ft_isalpha(arg[i]) && !ft_isdigit(arg[i]) && arg[i] != '_')
			return (0);
	}
	return (1);
}

static int	remove_element(t_dblist **list, char *arg)
{
	t_dblist	*element;

	if (!*list || !arg)
		return (0);
	element = get_dblst_at_key(*list, arg);
	if (!element)
		return (0);
	if (element == *list)
		*list = element->next;
	dblst_delone(element, free);
	return (1);
}

static int	exec_unset(t_data *d, char *arg)
{
	if (!arg)
		return (FCT_OK);
	if (!is_valid_identifier(arg))
	{
		ft_dprintf(2, "msh: unset: `%s': not a valid identifier\n", arg);
		return (CMD_NOT_FOUND);
	}
	if (!arg)
		return (FCT_FAIL);
	remove_element(&d->env_list, arg);
	remove_element(&d->var_list, arg);
	return (FCT_OK);
}

int	unset(t_data *d, char *arg, char **flags, int status)
{
	int			ret_val;
	int			i;

	(void)status;
	ret_val = exec_unset(d, arg);
	i = -1;
	while (flags && flags[++i])
	{
		if (exec_unset(d, flags[i]) != FCT_OK)
			ret_val = FCT_FAIL;
	}
	update_environ(d);
	return (ret_val);
}
