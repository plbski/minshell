/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:27:21 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/16 20:38:30 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

t_dblist	*get_dblst_node(t_dblist *lst, const char *content)
{
	t_dblist	*first_node;

	if (!lst)
		return (NULL);
	first_node = dblst_first(lst);
	if (same_str(first_node->content, content))
		return (first_node);
	lst = first_node->next;
	while (lst && lst != first_node)
	{
		if (same_str(lst->content, content))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

char	**get_base_env(t_data *d)
{
	char	**base_env;

	base_env = ms_malloc(d, sizeof(char *) * 6);
	base_env[0] = ms_strdup(d, "SHLVL=1");
	base_env[1] = ms_strdup(d, "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/\
			usr/bin:.:/.local/opt/go/bin:/go/bin");
	base_env[2] = ms_strdup(d, "_=/usr/bin/env");
	base_env[3] = ms_strjoin(d, ms_strdup(d, "PWD="), custom_get_cwd(d));
	base_env[4] = getenv("LOGNAME");
	base_env[5] = NULL;
	return (base_env);
}

void	init_env_list(t_data *d, char **env)
{
	char	**base_env;
	int		received_end;

	received_end = (env && env[0]);
	if (!received_end)
		base_env = get_base_env(d);
	if (d->env_list)
		dblst_clear(&d->env_list, free);
	if (received_end)
	{
		d->tmp_list = arr_to_dblst((void **)env);
		d->env_list = arr_to_dblst((void **)env);
	}
	else
	{
		d->env_list = arr_to_dblst((void **)base_env);
		d->tmp_list = arr_to_dblst((void **)base_env);
		d->environ = base_env;
	}
	if (!d->env_list)
		custom_exit(d, "List alloc failed", NULL, 1);
}

void	reorder_dblst(t_dblist *list)
{
	t_dblist	*db_b;
	char		*tmp;

	while (list)
	{
		db_b = list->next;
		while (db_b)
		{
			if (list->content && db_b->content && \
				ft_strcmp((char *)list->content, (char *)db_b->content) > 0)
			{
				tmp = list->content;
				list->content = db_b->content;
				db_b->content = tmp;
			}
			db_b = db_b->next;
		}
		list = list->next;
	}
}

static struct termios oldt;

void set_nonblocking_mode(int enable)
{
    struct termios newt;

    if (enable)
    {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        newt.c_cc[VMIN] = 0;  // Ne pas attendre un caractère
        newt.c_cc[VTIME] = 0; // Pas de timeout
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }
    else
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}