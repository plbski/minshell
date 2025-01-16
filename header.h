/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:04:55 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/15 16:46:43 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define cool 1
#ifndef HEADER_H
# define HEADER_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <time.h>
# include <fcntl.h>
# include <signal.h>

# define START_ANIM_TEXT "~~~ Minishell by gvlente & pbuet ~~~"
# define END_ANIM_TEXT	 "~~~ EXIT ~~~"

# define MAX_DIR_LEN 500
# define PROMPT_ICON "$ "

# define PROMPT_SQARE "U+2589"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define RESET "\033[0m"

typedef enum e_data_status
{
	running,
	closing,
	waiting,
}	t_status;

typedef struct s_data
{
	char		*cwd;
	char		*home;
	t_status	status;
}	t_data;

//		prompt.c
int		show_doc(char *prompt_line);
void	execute_prompt(t_data *d, char *prompt);
int		get_terminal_prompt(t_data *d);

//		utils.c
void	handle_sigint(int sig);

//		init.c
void	init_data(t_data *data);
char	*init_cwd(t_data *data);
int		write_animated_txt(char *txt_to_display, int interval, int exit_wait);
int		init_env(t_data *data);
void	ft_cd(t_data *d, char *arg);
void	pwd(t_data *d);

#endif