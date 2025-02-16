/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:56:26 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/16 15:26:00 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

t_tktype	get_token_type(int *was_cmd, char *str)
{
	if (same_str(str, "<"))
		return (tk_red_in);
	if (same_str(str, ">"))
		return (tk_red_out);
	if (same_str(str, ">>"))
		return (tk_red_app);
	if (same_str(str, "<<"))
		return (tk_hered);
	if (same_str(str, "|"))
		return (tk_pipe);
	if (same_str(str, "&&") || same_str(str, "||"))
		return (tk_logical);
	if (same_str(str, "*"))
		return (tk_wildcard);
	if (*was_cmd)
		return (tk_argument);
	return (tk_command);
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

static t_token	*get_split_tokens(t_data *d, char **splits, \
	int i, t_token *token)
{
	int			bracket;
	t_tktype	type;
	int			was_cmd;

	bracket = 0;
	was_cmd = 0;
	token = NULL;
	while (splits[++i])
	{
		if (same_str(splits[i], "(") || same_str(splits[i], ")"))
		{
			bracket += 2 * (splits[i][0] == '(') - 1;
			continue ;
		}
		type = get_token_type(&was_cmd, splits[i]);
		if (type == tk_command)
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

	splits = split_input(d, prompt);
	token = get_split_tokens(d, splits, -1, NULL);
	free_void_array((void ***)&splits);
	token = token_first(token);
	link_token_pipes(token);
	if (d->debug_mode)
		show_tokens_info(d, token, "init", "");
	return (token);
}
