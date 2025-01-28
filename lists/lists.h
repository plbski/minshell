/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:07:59 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/01/27 09:34:01 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H

# include <stdlib.h>
# include <stdio.h>

typedef struct s_circ_list
{
	void				*content;
	struct s_circ_list	*prev;
	struct s_circ_list	*next;
	struct s_circ_list	*head;
}	t_clst;

typedef struct s_dblink_list
{
	void					*content;
	struct s_dblink_list	*next;
	struct s_dblink_list	*prev;
}	t_dblist;

typedef struct s_dictionary
{
	char				*key;
	char				*value;
}	t_key_value;

//		DB_LIST
//			check
int			dblst_size(t_dblist *lst);
//			move
t_dblist	*dblst_first(t_dblist *lst);
t_dblist	*dblst_last(t_dblist *lst);
//			delete
void		dblst_clear(t_dblist **lst, void (*del)(void *));
void		dblst_delone(t_dblist *lst, void (*del)(void *));
//			initlear
t_dblist	*dblst_new(void *content);
t_dblist	*arr_to_dblst(void **values);
void		dblst_add_back(t_dblist **lst, t_dblist *node);
void		dblst_add_front(t_dblist **lst, t_dblist *node);
//			use
t_dblist	*dblst_map(t_dblist *lst, void *(*f)(void *), \
	void (*del)(void *));
void		dblst_iter(t_dblist *lst, void (*f)(void *));
t_dblist	*get_dblst_at_key(t_dblist *lst, char *prefix);
void		dblst_print_list(t_dblist *lst, int has_prefix);

//		CIRC_LIST
//		init
t_clst		*clst_new(void *content);
void		clst_add_back(t_clst **lst, t_clst *node);
void		clst_add_front(t_clst **lst, t_clst *node);
//		check
int			clst_size(t_clst *lst);
t_clst		*clst_last(t_clst *lst);
//		delete
void		clst_clear(t_clst **lst, void (*del)(void *));
void		clst_delone(t_clst *lst, void (*del)(void *));
//		use
t_clst		*clst_map(t_clst *lst, void *(*f)(void *), \
	void (*del)(void *));
void		clst_iter(t_clst *lst, void (*f)(void *));

//		UTILS
char		*list_strdup(const char *str);
char		**list_to_arr(t_dblist *l);

#endif
