/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 00:14:18 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/03/04 14:47:44 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

int	env(t_data *d, char *arg, char **flags, int has_prefix)
{
	(void)has_prefix;
	if (arg || flags)
	{
		ft_dprintf(2, "env: %s: No such file or directory\n", arg);
		return (FCT_FAIL);
	}
	if (!d->environ)
		ft_dprintf(2, "msh: env: No such file or directory\n");
	show_char_array("\n", d->environ, 0);
	return (FCT_OK);
}
