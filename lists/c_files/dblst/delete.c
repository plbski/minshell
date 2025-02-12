/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:23:03 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/12 14:07:09 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lists.h"

void	dblst_clear(t_dblist **lst, void (*del)(void *))
{
	t_dblist	*cur;
	t_dblist	*tmp;

	if (!lst || !*lst)
		return ;
	cur = dblst_first(*lst);
	while (cur)
	{
		tmp = cur->next;
		del(cur->content);
		free(cur);
		cur = tmp;
	}
	*lst = NULL;
}

void	dblst_delone(t_dblist *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del && lst->content)
		del(lst->content);
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
	free(lst);
}

void	print_content(void *content)
{
	if (content)
		printf("%s\n", (char *)content);
}

void	print_prefixed_content(void *content)
{
	char	*str;
	int		i;
	int		has_value;

	if (!content)
		return ;
	str = (char *)content;
	printf("declare -x ");
	i = -1;
	has_value = 0;
	while (str[++i])
	{
		if (str[i - 1] == '=' && !has_value)
		{
			has_value = 1;
			printf("\"");
		}
		printf("%c", str[i]);
	}
	if (i > 0 && str[i - 1] == '=' && !has_value)
		printf("\"\"");
	else if (has_value)
		printf("\"");
	printf("\n");
}

void	dblst_print_list(t_dblist *lst, int has_prefix)
{
	if (lst)
	{
		if (has_prefix)
			dblst_iter(lst, print_prefixed_content);
		else
			dblst_iter(lst, print_content);
	}
}
