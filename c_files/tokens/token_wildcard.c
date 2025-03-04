/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:44:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/27 16:18:50 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

void	sort_wildcard_tokens(t_token *tk)
{
	t_token	*b;
	t_token	*a;
	char	*tmp;

	a = token_first(tk);
	while (a)
	{
		b = a->next;
		while (b)
		{
			if (ft_strcmp(a->name, b->name) > 0)
			{
				tmp = a->name;
				a->name = b->name;
				b->name = tmp;
			}
			b = b->next;
		}
		a = a->next;
	}
}

int	validate_entry(char *entry_name, char *prefix, char *suffix)
{
	int	i;
	int	j;

	if (!entry_name || entry_name[0] == '.')
		return (0);
	i = -1;
	while (prefix && prefix[++i])
		if (!entry_name[i] || entry_name[i] != prefix[i])
			return (0);
	if (!suffix)
		return (1);
	i = ft_strlen(suffix);
	j = ft_strlen(entry_name);
	if (j < i)
		return (0);
	while (i >= 0)
		if (entry_name[j--] != suffix[i--])
			return (0);
	return (1);
}

static t_token	*get_wc_tokens(t_data *d, int brk, char *prefix, char *suffix)
{
	DIR				*directory;
	struct dirent	*entry;
	char			*entry_name;
	t_token			*wc_node;

	directory = get_directory(d, d->cwd);
	if (!directory)
		return (NULL);
	entry = readdir(directory);
	wc_node = NULL;
	while (entry)
	{
		entry_name = ms_strdup(d, entry->d_name);
		if (validate_entry(entry_name, prefix, suffix))
			wc_node = new_token(entry_name, wc_node, tk_arg, brk);
		free(entry_name);
		entry = readdir(directory);
	}
	return (closedir(directory), wc_node);
}

void	fill_uffix(t_data *d, char *str, char **suffix, char **prefix)
{
	char	**split;
	int		arr_len;

	split = ft_split(str, '*', '\0');
	if (!split)
		custom_exit(d, "alloc in uffix\n", NULL, FCT_FAIL);
	arr_len = get_arr_len((void **)split);
	if (split[0] && str[0] != '*')
		*prefix = ms_strdup(d, split[0]);
	if (split[arr_len - 1] && arr_len > 1)
		*suffix = ms_strdup(d, split[arr_len - 1]);
	else if (split[0] && str[0] == '*')
		*suffix = ms_strdup(d, split[0]);
	if (d->debug_mode)
		show_char_array("wc", split);
	free_void_array((void ***)&split);
}

t_token	*fill_wildcard(t_data *d, t_token *start, char *str, int brk)
{
	t_token			*wc_node;
	t_token			*wc_start;
	char			*prefix;
	char			*suffix;
	char			*to_check;

	to_check = ms_strdup(d, str);
	remove_chars(d, &to_check, "/");
	suffix = NULL;
	prefix = NULL;
	if (!same_str(to_check, "*"))
		fill_uffix(d, to_check, &suffix, &prefix);
	wc_node = get_wc_tokens(d, brk, prefix, suffix);
	safe_free(suffix);
	safe_free(prefix);
	if (!wc_node)
		return (new_token(to_check, start, tk_arg, brk));
	free(to_check);
	wc_start = token_first(wc_node);
	sort_wildcard_tokens(wc_start);
	wc_start->prv = start;
	start->next = wc_start;
	return (wc_node);
}
