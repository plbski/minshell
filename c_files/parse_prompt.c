/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:28:54 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/31 01:06:06 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	handle_direct_exec(t_data *d, char *cmd_name, char *arg, char **flags)
{
	char	**new_flg;
	int		i;
	int		arr_len;
	int		fct_ret;

	arr_len = get_arr_len((void **)flags) + 1;
	arg && (arr_len++);
	new_flg = malloc(sizeof(char *) * (arr_len + 1));
	!new_flg && (custom_exit(d, "alloc for flags", NULL, EXIT_FAILURE));
	new_flg[0] = ft_strdup(cmd_name);
	!new_flg[0] && (custom_exit(d, "alloc for flag[0]", NULL, EXIT_FAILURE));
	new_flg[1] = NULL;
	i = 0;
	if (arg)
	{
		new_flg[1] = ft_strdup(arg);
		!new_flg[1] && (custom_exit(d, "alloc > flag", NULL, EXIT_FAILURE));
		i = 1;
	}
	while (++i < arr_len)
	{
		new_flg[i] = ft_strdup(flags[i - 1 - (arg != NULL)]);
		!new_flg[i] && (custom_exit(d, "alloc > flag", NULL, EXIT_FAILURE));
	}
	new_flg[i] = NULL;
	fct_ret = exec(d, cmd_name, new_flg, 0);
	free_void_array((void ***)&new_flg);
	return (fct_ret);
}

//	echo "ola" -n (echo = cmd_name | "ola" = arg | -n = flags)
int	execute_command(t_data *d, char *cmd_name, char *arg, char **flags)
{
	int		i;

	if (d->debug_mode)
		search_true_cmd(d, cmd_name, arg, flags);
	if (access(cmd_name, X_OK) != -1)
		return (handle_direct_exec(d, cmd_name, arg, flags));
	if (!ft_strncmp(cmd_name, "./", 2))
		return (handle_direct_exec(d, cmd_name, arg, flags));
	else if (!ft_strncmp(cmd_name, "exec ", 5))
		return (handle_direct_exec(d, arg, NULL, flags));
	else if (ch_amount(cmd_name, '=') == 1)
		return (export(d, cmd_name, flags, 1));
	i = -1;
	while (d->bltin_names[++i])
	{
		if (is_same_string(d->bltin_names[i], cmd_name))
		{
			d->blt_fct[i](d, arg, flags, EXIT_SUCCESS);
			return (1);
		}
	}
	printf("msh: %s: command not found\n", cmd_name);
	return (0);
}

int	execute_prompt(t_data *d, char *prmpt)
{
	char		*arg;
	char		*cmd_name;
	char		**flags;
	t_token		*tokens;
	int			fct_ret;

	cmd_name = NULL;
	arg = NULL;
	flags = get_flags(d, prmpt, &cmd_name, &arg);
	(void)tokens;
	fct_ret = execute_command(d, cmd_name, arg, flags);
	if (dup2(1, STDOUT_FILENO) == -1)
		custom_exit(d, "erreur dup2", NULL, EXIT_FAILURE);
	if (dup2(0, STDOUT_FILENO) == -1)
		custom_exit(d, "erreur dup2", NULL, EXIT_FAILURE);
	if (d->fd)
		close(d->fd);
	d->fd = 0;
	free_void_array((void ***)&flags);
	safe_free(arg);
	safe_free(cmd_name);
	return (fct_ret);
}
