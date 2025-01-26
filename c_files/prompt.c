/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:51:46 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/26 12:36:08 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

/**
 * @note 
 * @attention 
 * @todo 
 */
int	handle_splits(t_data *d, char *prompt)
{
	char	**splits;
	int		i;

	(void)d;
	splits = ft_split_str(prompt, "&&");
	if (!splits)
		return (0);
	i = -1;
	while (splits[++i])
		execute_prompt(d, splits[i]);
	return (1);
}

int	is_valid_prompt(char *prompt)
{
	int	i;

	i = -1;
	while (prompt[++i])
	{
		if (prompt[i] != ' ')
			return (1);
	}
	return (0);
}

char	**init_tokens()
{
	
}

int	execute_prompt(t_data *d, char *prmpt)
{
	char	**tokens;
	char	*arg;
	char	*flag;
	int		i;

	if (!is_valid_prompt(prmpt))
		return (0);
	if (get_char_occurence(prmpt, '=') == 1 && ft_strncmp(prmpt, "export", 6))
		return (export(d, prmpt, NULL, 1));
	arg = NULL;
	flag = NULL;
	tokens = ft_split(prmpt, ' ');
	if (tokens)
	{
		i = -1;
		while (tokens[++i])
			(tokens[i][0] == '$' && (tokens[i] = get_env_value(d, tokens[i] + 1)));
		arg = tokens[1];
		if (arg)
			flag = tokens[2];
	}
	if (!ft_strncmp(tokens[0], "./", 2))
		return (exec(d, tokens[0], tokens[1], 0), \
			free_void_array((void ***)&tokens)), 1;
	i = -1;
	while (d->bltin_names[++i])
		if (!ft_strncmp(tokens[0], d->bltin_names[i], \
		ft_strlen(d->bltin_names[i])) && ft_strlen(tokens[0]) == ft_strlen(d->bltin_names[i]))
			return (d->builtin_funcs[i](d, arg, flag, EXIT_SUCCESS), \
				free_void_array((void ***)&tokens), 1);
	printf("mshell: %s: command not found\n", tokens[0]);
	return (free_void_array((void ***)&tokens), 0);
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
