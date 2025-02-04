/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:13:52 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/04 17:14:55 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	d_convert_and_print(int fd, unsigned int num, int to_upper)
{
	char	str[9];
	int		remainder;
	int		index;
	int		len;
	char	*hexdigits;

	len = 0;
	if (to_upper)
		hexdigits = "0123456789ABCDEF";
	else
		hexdigits = "0123456789abcdef";
	str[8] = '\0';
	index = 7;
	if (num == 0)
		str[index--] = '0';
	while (num > 0 && index >= 0)
	{
		remainder = num % 16;
		str[index--] = hexdigits[remainder];
		num /= 16;
	}
	len = d_putstr(fd, &str[index + 1]);
	return (len);
}

static int	d_print_value_num(int fd, char frm, va_list args)
{
	char	*str;
	int		len;

	len = 0;
	str = NULL;
	if (frm == 'd')
		str = d_itoa(va_arg(args, int));
	else if (frm == 'i')
		str = d_itoa(va_arg(args, int));
	else if (frm == 'u')
		str = d_utoa(va_arg(args, unsigned int));
	else if (frm == 'x')
		len += d_convert_and_print(fd, va_arg(args, unsigned int), 0);
	else if (frm == 'X')
		len += d_convert_and_print(fd, va_arg(args, unsigned int), 1);
	if (str != NULL)
	{
		len += d_putstr(fd, str);
		free(str);
	}
	else if (frm != 'x' && frm != 'X')
		return (-1);
	return (len);
}

static int	d_print_value(int fd, char frm, va_list args)
{
	if (frm == 'd' || frm == 'i' || frm == 'u' || frm == 'x' || frm == 'X')
		return (d_print_value_num(fd, frm, args));
	if (frm == 'c')
		return (d_putchar(fd, va_arg(args, int)));
	if (frm == 's')
		return (d_putstr(fd, va_arg(args, char *)));
	if (frm == 'p')
		return (d_putptr(fd, va_arg(args, void *)));
	if (frm == '%')
		return (d_putchar(fd, '%'));
	return (-1);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		cur_len;
	int		len;
	int		i;

	va_start(args, format);
	len = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			cur_len = d_print_value(fd, format[i + 1], args);
			if (cur_len == -1)
				return (-1);
			len += cur_len;
			format++;
		}
		else if (d_putchar(fd, format[i]) == -1)
			return (-1);
		else
			len++;
		i++;
	}
	return (len);
}
