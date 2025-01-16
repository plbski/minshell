/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:13:52 by gvalente          #+#    #+#             */
/*   Updated: 2024/10/23 14:14:09 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_convert_and_print(unsigned int num, int to_upper)
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
	len = ft_putstr(&str[index + 1]);
	return (len);
}

int	print_value_num(char frm, va_list args)
{
	char	*str;
	int		len;

	len = 0;
	str = NULL;
	if (frm == 'd')
		str = ft_itoa(va_arg(args, int));
	else if (frm == 'i')
		str = ft_itoa(va_arg(args, int));
	else if (frm == 'u')
		str = ft_utoa(va_arg(args, unsigned int));
	else if (frm == 'x')
		len += ft_convert_and_print(va_arg(args, unsigned int), 0);
	else if (frm == 'X')
		len += ft_convert_and_print(va_arg(args, unsigned int), 1);
	if (str != NULL)
	{
		len += ft_putstr(str);
		free(str);
	}
	else if (frm != 'x' && frm != 'X')
		return (-1);
	return (len);
}

int	print_value(char frm, va_list args)
{
	if (frm == 'd' || frm == 'i' || frm == 'u' || frm == 'x' || frm == 'X')
		return (print_value_num(frm, args));
	if (frm == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (frm == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (frm == 'p')
		return (ft_putptr(va_arg(args, void *)));
	if (frm == '%')
		return (ft_putchar('%'));
	return (-1);
}

int	ft_printf(const char *format, ...)
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
			cur_len = print_value(format[i + 1], args);
			if (cur_len == -1)
				return (-1);
			len += cur_len;
			format++;
		}
		else if (ft_putchar(format[i]) == -1)
			return (-1);
		else
			len++;
		i++;
	}
	return (len);
}
