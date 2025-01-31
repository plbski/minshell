/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:56:26 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/31 20:08:37 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

t_toktype	get_token_type_2(t_data *d, char *str, t_token *prev)
{
	(void)d;
	if (chr_amnt(str, '\''))
		return (tk_quote);
	if (chr_amnt(str, '\"'))
		return (tk_dbquote);
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

int	requires_arg(t_token *node)
{
	return (node->type == tk_red_app || node->type == tk_red_in || \
	node->type == tk_red_out || node->type == tk_pipe || \
	node->type == tk_logical || node->type == tk_hered);
}

int	validate_token(t_token *node)
{
	t_toktype	typ;

	typ = node->type;
	if (typ != tk_command && typ != tk_exec && typ != tk_hered && !chr_amnt(node->name, '=') && !node->prv)
	{
		printf("msh: command not found: %s\n", node->name);
		return (0);
	}
	if (requires_arg(node) && !node->next)
	{
		printf("msh: parse error near \'%s\'\n", node->name);
		return (0);
	}
	return (1);
}

int	is_directory(const char *path)
{
	struct stat	entry_stat;

	if (stat(path, &entry_stat) == 0)
		return ((entry_stat.st_mode & S_IFMT) == S_IFDIR);
	return (0);
}

t_token	*fill_wildcard(t_data *d, t_token *start)
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
		if (is_directory(arg_name))
			start = new_token(arg_name, start, tk_argument);
		entry = readdir(directory);
	}
	return (start);
}

t_token	*tokenize_string(t_data *d, char *prompt)
{
	char		**splits;
	t_token		*token;
	t_toktype	type;
	int			i;

	splits = split_prompt(prompt, ' ');
	token = NULL;
	i = -1;
	while (splits[++i])
	{
		type = get_token_type(d, splits[i], token);
		if (type == tk_wildcard)
			token = fill_wildcard(d, token);
		else
			token = new_token(splits[i], token, type);
	}
	if (d->debug_mode)
		show_tokens_info(token, "init");
	return (token);
}
