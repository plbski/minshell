/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:51:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/26 18:33:46 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	handle_direct_exec(t_data *d, char *cmd_name, char *arg, char **flags)
{
	char	**exec_flags;
	int		i;
	int		arr_len;

	arr_len = get_arr_len((void **)flags) + 1;
	if (arg)
		arr_len++;
	exec_flags = malloc(sizeof(char *) * arr_len);
	if (!exec_flags)
		custom_exit(d, "Malloc fail for exec_flags", NULL, EXIT_FAILURE);
	exec_flags[0] = ft_strdup(cmd_name);
	if (!exec_flags[0])
		custom_exit(d, "Malloc fail for exec_flags", NULL, EXIT_FAILURE);
	exec_flags[1] = NULL;
	if (arg)
	{
		exec_flags[1] = ft_strdup(arg);
		if (!exec_flags[1])
			custom_exit(d, "Malloc fail for exec_flags", NULL, EXIT_FAILURE);
		i = 1;
	}
	else
		i = 0;
	while (++i < arr_len)
	{
		exec_flags[i] = ft_strdup(flags[i - 1 - (arg != NULL)]);
		if (!exec_flags[i])
			custom_exit(d, "Malloc fail for exec_flag", NULL, EXIT_FAILURE);
	}
	exec_flags[i] = NULL;
	exec(d, cmd_name, exec_flags, 0);
	return (free_void_array((void ***)&exec_flags), 1);
}

//	echo "ola" -n (echo = cmd_name | "ola" = arg | -n = flags)
int	execute_command(t_data *d, char *cmd_name, char *arg, char **flags)
{
	int		i;

	if (!ft_strncmp(cmd_name, "./", 2))
		return (handle_direct_exec(d, cmd_name, arg, flags), 1);
	else if (!ft_strncmp(cmd_name, "exec ", 5))
		return (handle_direct_exec(d, arg, NULL, flags), 1);
	else if (get_char_occurence(cmd_name, '=') == 1)
		return (export(d, cmd_name, flags, 1));
	else if (is_same_string(cmd_name, "export") && get_char_occurence(arg, '=') == 1)
		return (export(d, arg, flags, 1));
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

int	is_valid_prompt(char *prompt)
{
	int	i;

	if (!prompt)
		return (0);
	i = -1;
	while (prompt[++i])
	{
		if (prompt[i] != ' ')
			return (1);
	}
	return (0);
}

int	execute_prompt(t_data *d, char *prmpt)
{
	char		*arg;
	char		*cmd_name;
	char		**flags;

	if (!is_valid_prompt(prmpt))
		return (0);
	cmd_name = NULL;
	arg = NULL;
	flags = get_flags(d, prmpt, &cmd_name, &arg);
	execute_command(d, cmd_name, arg, flags);
	free_void_array((void ***)&flags);
	safe_free(arg);
	safe_free(cmd_name);
	return (1);
}

char	*get_prompt_message(t_data *d)
{
	char	*logname_part;
	char	*cwd_part;
	char	*prompt_msg;
	char	*icon_part;

	logname_part = ft_str_mega_join(PROMPT_LOGNAME_COL, d->logname, " ", RESET);
	if (!logname_part)
		return (NULL);
	icon_part = ft_str_mega_join(MAGENTA, "$ ", RESET, NULL);
	cwd_part = ft_str_mega_join(PROMPT_CWD_COL, d->cwd, icon_part, RESET);
	prompt_msg = ft_strjoin(logname_part, cwd_part);
	free(icon_part);
	free(cwd_part);
	free(logname_part);
	return (prompt_msg);
}

int	get_terminal_prompt(t_data *d)
{
	char	*prompt_msg;
	char	*terminal_line;

	if (!d->cwd)
		custom_exit(d, "No cwd", NULL, EXIT_FAILURE);
	prompt_msg = get_prompt_message(d);
	if (!prompt_msg)
		custom_exit(d, "Prompt alloc failed", NULL, EXIT_FAILURE);
	terminal_line = readline(prompt_msg);
	if (!terminal_line)
		custom_exit(d, NULL, NULL, EXIT_SUCCESS);
	add_history(terminal_line);
	handle_splits(d, terminal_line);
	free(terminal_line);
	free(prompt_msg);
	return (1);
}
