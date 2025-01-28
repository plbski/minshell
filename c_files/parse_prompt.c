/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:28:54 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/28 10:51:28 by giuliovalen      ###   ########.fr       */
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
	new_flg = malloc(sizeof(char *) * arr_len);
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

char	*get_dir_in_path(t_data *d, char *cmd_name)
{
	char	*path_env;
	char	**splitted_path;
	char	*cmd_path;
	int		i;

	path_env = get_env_value(d, d->env_list, "PATH");
	if (!path_env)
		custom_exit(d, "PATH not found in environment", NULL, EXIT_FAILURE);
	splitted_path = ft_split(path_env, ':');
	free(path_env);
	if (!splitted_path)
		custom_exit(d, "Failed to split PATH", NULL, EXIT_FAILURE);
	cmd_path = NULL;
	i = -1;
	while (splitted_path[++i])
	{
		cmd_path = ft_str_mega_join(splitted_path[i], "/", cmd_name, NULL);
		if (access(cmd_path, X_OK) == 0)
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	free_void_array((void ***)&splitted_path);
	return (cmd_path);
}

int	search_true_cmd(t_data *d, char *cmd_name, char *arg, char **flags)
{
	char	*path_cmd;

	path_cmd = get_dir_in_path(d, cmd_name);
	if (path_cmd)
	{
		printf("____________True shell cmd outpout________\n");
		handle_direct_exec(d, path_cmd, arg, flags);
		printf("____________minishell command__________\n");
		return (1);
	}
	return (0);
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
	else if (get_char_occurence(cmd_name, '=') == 1)
		return (export(d, cmd_name, flags, 1));
	i = -1;
	while (d->bltin_names[++i])
	{
		if (is_same_string(d->bltin_names[i], cmd_name))
		{
			d->builtin_funcs[i](d, arg, flags, EXIT_SUCCESS);
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
	int			fct_ret;

	cmd_name = NULL;
	arg = NULL;
	flags = get_flags(d, prmpt, &cmd_name, &arg);
	fct_ret = execute_command(d, cmd_name, arg, flags);
	free_void_array((void ***)&flags);
	safe_free(arg);
	safe_free(cmd_name);
	return (fct_ret);
}
