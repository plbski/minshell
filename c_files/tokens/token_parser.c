/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:56:26 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/07 23:55:40 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static t_toktype	get_token_type_2(t_data *d, int *was_cmd, char *str, t_token *prev)
{
	char	*bin_str;

	(void)d;
	if (cmp_str(str, "..") || cmp_str(str, "."))
		return (tk_argument);
	if (!prev || (prev->type != tk_exec && prev->type != tk_command))
	{
		if (str[0] == '.' && str[1] == '/')
			return (tk_exec);
		if (access(str, X_OK) != -1)
			return (tk_exec);
		bin_str = ms_strjoin(d, "/bin/", str);
		if (access(bin_str, F_OK) != -1 && access(bin_str, X_OK) != -1)
		{
			free(bin_str);
			*was_cmd = 1;
			return (tk_exec);
		}
		free(bin_str);
	}
	return (tk_argument);
}

t_toktype	get_token_type(t_data *d, int *was_cmd, char *str, t_token *prev)
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
	return (get_token_type_2(d, was_cmd, str, prev));
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
	int			was_cmd;

	bracket = 0;
	i = -1;
	was_cmd = 0;
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
		type = get_token_type(d, &was_cmd, splits[i], token);
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

	splits = split_prompt(d, prompt);
	token = get_split_token(d, splits);
	free_void_array((void ***)&splits);
	token = token_first(token);
	link_token_pipes(token);
	if (d->debug_mode)
		show_tokens_info(d, token, "init", "");
	return (token);
}
