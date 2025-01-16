/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:04:55 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/15 00:16:09 by gvalente         ###   ########.fr       */
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
# include <dirent.h>

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
	char		*doc_wd;
	char		*start_wd;
	t_status	status;
}	t_data;

//		init.c
void	init_data(t_data *data);
int		init_cwd(t_data *data);
int		write_animated_txt(char *txt_to_display, int interval, int exit_wait);
int		init_env(t_data *data);

//		prompt.c
void	execute_prompt(t_data *d, char *prompt);
int		get_terminal_prompt(t_data *d);

//		functions.c
void    pwd(t_data *d);
void    cd(t_data *d, char *prompt);
int		man(t_data *d, char *prompt_line);
int		ls(t_data *d);

//		utils.c
void	handle_sigint(int sig);
char 	*ft_remove_prefix(char *str, char *prefix);
char	*truncate_at_end(char *str, const char cut_letter);
int		update_cwd(t_data *data);
char	*get_next_line(int fd);

#endif