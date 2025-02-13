/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:28:54 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/13 01:57:07 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	handle_direct_exec(t_data *d, char *cmd_name, char *arg, char **flags)
{
	char	**new_flg;
	char	*rm_name;
	int		i;
	int		arr_len;
	int		fct_ret;

	rm_name = ms_strdup(d, cmd_name);
	arr_len = get_arr_len((void **)flags) + 1;
	if (arg)
		arr_len++;
	new_flg = ms_malloc(d, sizeof(char *) * (arr_len + 1));
	new_flg[0] = ms_strdup(d, rm_name);
	new_flg[1] = NULL;
	i = 0;
	if (arg)
	{
		new_flg[1] = ms_strdup(d, arg);
		i = 1;
	}
	while (++i < arr_len)
		new_flg[i] = ms_strdup(d, flags[i - 1 - (arg != NULL)]);
	new_flg[i] = NULL;
	fct_ret = exec(d, rm_name, new_flg, 1);
	free_void_array((void ***)&new_flg);
	return (free(rm_name), fct_ret);
}

//	echo "ola" -n (echo = cmd_name | "ola" = arg | -n = flags)
int	execute_command(t_data *d, char *cmd_name, char *arg, char **flags)
{
	int		i;

	i = -1;
	while (d->bltin_names[++i])
		if (cmp_str(d->bltin_names[i], cmd_name))
			return (d->blt_fct[i](d, arg, flags, EXIT_SUCCESS));
	if (cmp_str(cmd_name, "var") && d->var_list)
		return (dblst_print_list(d->var_list, 0), FCT_SUCCESS);
	else if (chr_amnt(cmd_name, '=') == 1)
		return (export(d, cmd_name, flags, 1));
	else if (cmp_str(cmd_name, "declare") && arg && cmp_str(arg, "-x"))
		return (export(d, flags[0], &flags[1], 0));
	else if (cmp_str(cmd_name, "declare"))
		return (export(d, arg, flags, 1));
	return (handle_direct_exec(d, cmd_name, arg, flags));
}
