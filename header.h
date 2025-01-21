/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:04:55 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/21 17:32:41 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define cool 1
#ifndef HEADER_H
# define HEADER_H

# include "libft/libft.h"
# include "lists/lists.h"
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

# define PROMPT_SQARE "U+2589"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define RESET "\033[0m"

# define PROMPT_LOGNAME_COL 	GREEN
# define PROMPT_CWD_COL			YELLOW

typedef enum e_data_status
{
	running,
	quitting,
	waiting,
}	t_status;

typedef struct s_data
{
	int			debug_mode;
	char		*cwd;
	char		*prev_cwd;
	char		*doc_wd;
	char		*start_wd;
	char		*home_wd;
	char		*logname;
	t_dblist	*env;
	t_status	status;
}	t_data;

//		init.c
void	init_data(t_data *data);
int		init_cwd(t_data *data);
int		write_animated_txt(char *txt_to_display, int interval, int exit_wait);
void	init_env_variables(t_data *d);

//		prompt.c
void	execute_prompt(t_data *d, char *prompt);
int		get_terminal_prompt(t_data *d);
void	export_env(t_data *d, char *prompt);

//		functions.c
void	pwd(t_data *d);
void	cd(t_data *d, char *prompt);
int		man(t_data *d, char *prompt_line);
int		ls(t_data *d);
void	custom_exit(t_data *data, int status);

//		signal
void	setup_signal(void);

//		utils_parsing
char	*ft_remove_prefix(char *str, char *prefix);
char	*truncate_at_end(char *str, const char cut_letter);
int		update_cwd(t_data *data);
char	*get_next_line(int fd);
int		create_file(t_data *d, char *content, char *file_name);
char	*get_array_element_with_prefix(char **array, char *prefix);
char	*ft_str_mega_join(char *a, char *b, char *c, char *d);
int		get_char_occurence(char *str, char c);

//		utils_design
void	set_string_color(char **str, char *color);

//		env
int		update_env_variables(t_data *d);
void	show_env(t_data *d);

//		free
void	safe_free(void *line);
int		free_void_array(void ***item);

#endif