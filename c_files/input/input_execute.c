/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:28:54 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/14 03:58:29 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

char	**get_flags(t_data *d, const char *name, const char *arg, char **flags)
{
	char	**new_flg;
	int		arr_len;
	int		i;

	arr_len = get_arr_len((void **)flags) + 1;
	if (arg)
		arr_len++;
	new_flg = ms_malloc(d, sizeof(char *) * (arr_len + 1));
	new_flg[0] = ms_strdup(d, name);
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
	return (new_flg);
}

int	handle_direct_exec(t_data *d, char *cmd_name, char *arg, char **flags)
{
	char	**new_flg;
	char	*rm_name;
	int		fct_ret;

	rm_name = ms_strdup(d, cmd_name);
	if (!ft_strncmp(rm_name, "./", 2))
		replace_strstr(d, &rm_name, ".", d->cwd);
	if (is_directory(rm_name) || access(rm_name, F_OK) == -1)
		setstr(d, &rm_name, ms_strdup(d, cmd_name));
	new_flg = get_flags(d, rm_name, arg, flags);
	fct_ret = exec(d, rm_name, new_flg, 1);
	free_void_array((void ***)&new_flg);
	free(rm_name);
	return (fct_ret);
}

//	echo "ola" -n (echo = cmd_name | "ola" = arg | -n = flags)
int	execute_command(t_data *d, char *cmd_name, char *arg, char **flags)
{
	int		i;

	if (same_str(cmd_name, "exec") && arg && !ft_strncmp(arg, "./", 2))
	{
		arg = ft_strdup(arg);
		replace_strstr(d, &arg, ".", d->cwd);
	}
	if (!cmd_name || same_str(cmd_name, "null"))
		return (FCT_OK);
	i = -1;
	while (d->bltin_names[++i])
		if (same_str(d->bltin_names[i], cmd_name))
			return (d->blt_fct[i](d, arg, flags, EXIT_SUCCESS));
	if (same_str(cmd_name, "var") && d->var_list)
		return (dblst_print_list(d->var_list, 0), FCT_OK);
	else if (chr_amnt(cmd_name, '=') == 1)
		return (export(d, cmd_name, flags, 1));
	else if (same_str(cmd_name, "declare") && arg && same_str(arg, "-x"))
		return (export(d, flags[0], &flags[1], 0));
	else if (same_str(cmd_name, "declare"))
		return (export(d, arg, flags, 1));
	return (handle_direct_exec(d, cmd_name, arg, flags));
}

int	exec_input(t_data *d, char *input)
{
	t_token		*tokens;
	t_token		*start;

	tokens = tokenize_string(d, input);
	if (!tokens)
		return (FCT_FAIL);
	start = token_first(tokens);
	iterate_tokens(d, start);
	if (d->heredocfd != -1)
		consumate_heredoc(d, NULL, NULL, NULL);
	if (d->debug_mode)
		show_tokens_info(d, start, "End ");
	clear_tokens(start);
	return (FCT_OK);
}
