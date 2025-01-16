/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:14:16 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/14 21:17:14 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

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

#endif