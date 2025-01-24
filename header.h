/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:04:55 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/24 14:02:31 by giuliovalen      ###   ########.fr       */
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
# include <time.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

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

typedef enum e_builtins
{
	e_cd,
	e_clear,
	e_echo,
	e_env,
	e_exit,
	e_export,
	e_ls,
	e_man,
	e_pwd,
	e_unset
}	t_builtins_types;

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
	char		*history_wd;
	char		*home_wd;
	char		*logname;
	char		**environ;
	t_dblist	*env_list;
	t_status	status;
	char		**bltin_names;
	int			(*builtin_funcs[])(struct s_data *data, \
		char *arg, char *flag, int status);
}	t_data;

int		g_sa_quit;

//		init.c
void	init_data(t_data *data, char **env);
int		init_cwd(t_data *data);
int		write_animated_txt(char *txt_to_display, int interval, int exit_wait);
void	update_env_list(t_data *d, char **env);

//		prompt.c
void	execute_prompt(t_data *d, char *prompt);
int		get_terminal_prompt(t_data *d);

//		builtins
int		cd(t_data *d, char *arg, char *flags, int status);
int		clear(t_data *d, char *arg, char *flags, int status);
int		echo(t_data *d, char *arg, char *flags, int status);
int		env(t_data *d, char *arg, char *flags, int status);
int		custom_exit(t_data *data, char *arg, char *flags, int status);
int		export(t_data *d, char *arg, char *flags, int status);
int		ls(t_data *d, char *arg, char *flags, int status);
int		man(t_data *d, char *arg, char *flags, int status);
int		pwd(t_data *d, char *arg, char *flags, int status);
int		unset(t_data *d, char *arg, char *flags, int status);

//		utils
void	update_environ(t_data *d);
char	*get_env_value(t_data *d, char *key);
void	update_env_list(t_data *d, char **env);
int		update_env_variables(t_data *d);
void	reorder_dblst(t_dblist *list);

//		signal
void	setup_signal(void);

//		utils_parsing
char	*ft_remove_prefix(char *str, char *prefix);
char	*truncate_at_end(char *str, const char cut_letter);
int		update_cwd(t_data *data);
char	*get_next_line(int fd);
char	*get_array_element_with_prefix(char **array, char *prefix);
char	*ft_str_mega_join(char *a, char *b, char *c, char *d);
int		get_char_occurence(char *str, char c);

//		utils_design
void	set_string_color(char **str, char *color);

//		env
int		update_env_variables(t_data *d);
void	update_environ(t_data *d);

//		STRSTR
char	**ft_split_str(char *str, char *sep);
char	*ft_strstr(char *str, char *to_find);
char	*remove_char(char **txt, char c);

//		free
void	safe_free(void *line);
int		free_void_array(void ***item);
int		free_data(t_data *data);

int		write_at_rel_path(t_data *d, char *content, char *file_name);
int		write_at_abs_path(char *content, char *path, int flags);

#endif