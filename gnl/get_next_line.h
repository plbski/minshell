/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:14:16 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/11 08:48:06 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "stdlib.h"
# include "unistd.h"
# include "stdio.h"

# define MAXSIZE 99999

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30
# endif

typedef struct s_t_data
{
	char	buffer[MAXSIZE];
	char	leftover[MAXSIZE];
}	t_data;

char	*get_next_line(int fd);
int		contains(const char *s, char c);
char	*ft_strdup(const char *s);
int		update_fd(t_data *d, int fd, int index, ssize_t b_read);
char	*handle_leftover(t_data *d);

#endif