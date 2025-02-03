/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:56:26 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/03 14:20:29 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static t_toktype	get_token_type_2(t_data *d, char *str, t_token *prev)
{
	(void)d;
	if (cmp_str(str, "*"))
		return (tk_wildcard);
	if (cmp_str(str, "..") || cmp_str(str, "."))
		return (tk_argument);
	if (!prev || (prev->type != tk_exec && prev->type != tk_command))
	{
		if (str[0] == '.' && str[1] == '/')
			return (tk_exec);
		if (access(str, X_OK) != -1)
			return (tk_exec);
	}
	return (tk_argument);
}

t_toktype	get_token_type(t_data *d, char *str, t_token *prev)
{
	int	i;

	if (prev && (prev->type == tk_red_out || prev->type == tk_red_app))
		return (tk_argument);
	if (!prev || prev->type == tk_pipe || prev->type == tk_logical || \
		prev->type == tk_argument)
	{
		i = -1;
		while (d->bltin_names[++i])
			if (cmp_str(str, d->bltin_names[i]))
				return (tk_command);
	}
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
	return (get_token_type_2(d, str, prev));
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
	t_toktype	type;

	bracket = 0;
	i = -1;
	token = NULL;
	while (splits[++i])
	{
		if (cmp_str(splits[i], "(") || cmp_str(splits[i], ")"))
		{
			bracket++;
			if (splits[i][0] == ')')
				bracket -= 2;
			continue ;
		}
		type = get_token_type(d, splits[i], token);
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
	if (d->debug_mode)
		show_tokens_info(d, token, "init");
	return (token);
}
