/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:18:37 by gvalente          #+#    #+#             */
/*   Updated: 2024/10/03 17:19:27 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	long	nmb;

	nmb = n;
	if (nmb < 0)
	{
		nmb = -nmb;
		write(fd, "-", 1);
	}
	if (nmb >= 10)
		ft_putnbr_fd(nmb / 10, fd);
	c = (nmb % 10) + '0';
	write(fd, &c, 1);
}
