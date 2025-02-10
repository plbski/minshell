/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:56:26 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/10 11:23:53 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

t_tktype	get_token_type(t_data *d, int *was_cmd, char *str, t_token *prev)
{
	if (cmp_str(str, "<"))
		return (tk_red_in);
	if (cmp_str(str, ">"))
		return (tk_red_out);
	if (cmp_str(str, ">>"))
		return (tk_red_app);
	if (cmp_str(str, "<<"))
		return (tk_hered);
	if (cmp_str(str, "|"))
		return (tk_pipe);
	if (cmp_str(str, "&&") || cmp_str(str, "||"))
		return (tk_logical);
	if (cmp_str(str, "*"))
		return (tk_wildcard);
	if (*was_cmd)
		return (tk_argument);
	if (is_builtin_cmd(d, str) && (!prev || prev->type == tk_pipe \
	|| prev->type == tk_logical || prev->type == tk_argument))
		return (*was_cmd = 1, tk_command);
	return (tk_exec);
}

static t_token	*fill_wildcard(t_data *d, t_token *start, int brk)
{
	DIR				*directory;
	struct dirent	*entry;
	char			*arg_name;

	directory = get_directory(d, d->cwd);
	if (!directory)
		custom_exit(d, "no dir for wildcard", NULL, EXIT_FAILURE);
	entry = readdir(directory);
	while (entry)
	{
		arg_name = ms_strdup(d, entry->d_name);
		if (arg_name[0] != '.')
			start = new_token(ms_strdup(d, arg_name), start, tk_argument, brk);
		free(arg_name);
		entry = readdir(directory);
	}
	closedir(directory);
	return (start);
}

static t_token	*get_split_token(t_data *d, char **splits)
{
	int			i;
	t_token		*token;
	int			bracket;
	t_tktype	type;
	int			was_cmd;

	bracket = 0;
	i = -1;
	was_cmd = 0;
	token = NULL;
	while (splits[++i])
	{
		if (cmp_str(splits[i], "(") || cmp_str(splits[i], ")"))
		{
			bracket += 2 * (splits[i][0] == '(') - 1;
			continue ;
		}
		type = get_token_type(d, &was_cmd, splits[i], token);
		if (type == tk_command || type == tk_exec)
			was_cmd = 1;
		else if (type == tk_pipe || type == tk_logical)
			was_cmd = 0;
		if (type == tk_wildcard)
			token = fill_wildcard(d, token, bracket);
		else
			token = new_token(ms_strdup(d, splits[i]), token, type, bracket);
	}
	return (token);
}

t_token	*tokenize_string(t_data *d, char *prompt)
{
	char		**splits;
	t_token		*token;

	splits = split_prompt(d, prompt);
	token = get_split_token(d, splits);
	free_void_array((void ***)&splits);
	token = token_first(token);
	link_token_pipes(token);
	if (d->debug_mode)
		show_tokens_info(d, token, "init", "");
	return (token);
}
