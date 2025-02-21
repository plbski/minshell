/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_style.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 23:17:45 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/21 15:13:04 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_STYLE_H
# define MSH_STYLE_H

# define START_ANIM_TEXT "~~~ Minishell by gvlente & pbuet ~~~ lv "

# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define YELLOW			"\033[33m"
# define BLUE			"\033[34m"
# define MAGENTA		"\033[35m"
# define CYAN			"\033[36m"
# define RESET			"\033[0m"
# define GREY			"\033[38;5;240m"
# define LIGHT_GREY		"\033[38;5;250m"
# define BLU_GRY		"\033[38;5;146m"
# define PALE_ROSE		"\033[38;5;217m"
# define PRP_LAV	"\033[38;5;183m"
# define MENTHA_GREEN	"\033[38;5;121m"
# define PASTEL_BLUE	"\033[38;5;110m"

# define DR0  "\033[38;5;255m"  // Blanc cassé
# define DR1  "\033[38;5;252m"  // Gris très clair
# define DR2  "\033[38;5;250m"  // Gris clair
# define DR3  "\033[38;5;247m"  // Gris moyen-clair
# define DR4  "\033[38;5;244m"  // Gris moyen
# define DR5  "\033[38;5;240m"  // Gris moyen-foncé
# define DR6  "\033[38;5;237m"  // Gris foncé
# define DR7  "\033[38;5;235m"  // Gris très foncé
# define DR8  "\033[38;5;233m"  // Presque noir

# define DR9  "\033[38;5;130m"  // Brun/Orange foncé
# define DR10 "\033[38;5;136m"  // Orange foncé
# define DR11 "\033[38;5;172m"  // Orange
# define DR12 "\033[38;5;208m"  // Orange vif
# define DR13 "\033[38;5;214m"  // Orange clair
# define DR14 "\033[38;5;220m"  // Jaune-orangé
# define DR15 "\033[38;5;226m"  // Jaune vif
# define DR16 "\033[38;5;196m"  // Rouge intense

# define DB0  "\033[38;5;32m"   // Bleu foncé
# define DB1  "\033[38;5;33m"   // Bleu profond
# define DB2  "\033[38;5;39m"   // Bleu moyen
# define DB3  "\033[38;5;45m"   // Bleu ciel
# define DB4  "\033[38;5;51m"   // Bleu léger
# define DB5  "\033[38;5;57m"   // Bleu clair
# define DB6  "\033[38;5;63m"   // Bleu très clair
# define DB7  "\033[38;5;69m"   // Bleu pastel
# define DB8  "\033[38;5;75m"   // Bleu azur
# define DB9  "\033[38;5;81m"   // Bleu électrique
# define DB10 "\033[38;5;87m"   // Bleu vif
# define DB11 "\033[38;5;93m"   // Bleu cobalt
# define DB12 "\033[38;5;99m"   // Bleu turquoise
# define DB13 "\033[38;5;105m"  // Bleu pervenche
# define DB14 "\033[38;5;111m"  // Bleu très clair
# define DB15 "\033[38;5;117m"  // Bleu lavande
# define DB16 "\033[38;5;123m"  // Bleu clair pur

# define D0  "\001\033[38;5;255m\002"
# define D1  "\001\033[38;5;252m\002"
# define D2  "\001\033[38;5;250m\002"
# define D3  "\001\033[38;5;247m\002"
# define D4 "\001\033[38;5;244m\002"
# define DRESET "\001\033[0m\002"

# define RLCL "\001"
# define RLSTP
# define PRM_SEGLEN 2000
# define PRM_START	DB12
# define PRM_CWD	GREEN
# define PRM_HEAD	"\001\033[38;5;255m\002"
# define PRM_CMB	BLU_GRY

#endif