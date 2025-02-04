/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:49:09 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/04 17:14:03 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>

# define HEXDIGITS_MAJ "0123456789ABCDEF"
# define HEXDIGITS_MIN "0123456789abcdef"

int		ft_dprintf(int fd, const char *format, ...);
char	*d_itoa(int n);
int		d_putchar(int fd, char c);
int		d_putstr(int fd, char *str);
char	*d_strdup(const char	*s1);
int		d_strlen(const char *src);
int		d_putptr(int fd, void *ptr);
char	*d_utoa(unsigned int n);

#endif
