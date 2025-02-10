/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:28:54 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/10 17:50:36 by gvalente         ###   ########.fr       */
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

	rm_name = ft_remove_prefix(d, cmd_name, "./");
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
	fct_ret = exec(d, rm_name, new_flg, 0);
	free_void_array((void ***)&new_flg);
	return (free(rm_name), fct_ret);
}

//	echo "ola" -n (echo = cmd_name | "ola" = arg | -n = flags)
int	execute_command(t_data *d, char *cmd_name, char *arg, char **flags)
{
	int		i;

	if (access(cmd_name, X_OK) != -1)
		return (handle_direct_exec(d, cmd_name, arg, flags));
	if (cmd_name[0] == '.' && cmd_name[1] == '/')
		return (handle_direct_exec(d, cmd_name, arg, flags));
	else if (!ft_strncmp(cmd_name, "exec", 5))
		return (handle_direct_exec(d, arg, NULL, flags));
	else if (chr_amnt(cmd_name, '=') == 1)
		return (export(d, cmd_name, flags, 1));
	i = -1;
	while (d->bltin_names[++i])
		if (cmp_str(d->bltin_names[i], cmd_name))
			return (d->blt_fct[i](d, arg, flags, EXIT_SUCCESS));
	return (handle_direct_exec(d, cmd_name, arg, flags));
}
