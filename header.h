/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:04:55 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/26 18:18:45 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define START_ANIM_TEXT "			~~~ Minishell by gvlente & pbuet ~~~ "
# define END_ANIM_TEXT	 "					~~~ EXIT ~~~ "
# define MAX_DIR_LEN 500

# define PROMPT_SQARE "U+2589"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define RESET "\033[0m"

# define PROMPT_LOGNAME_COL 	CYAN
# define PROMPT_CWD_COL			YELLOW

# define _UNUSED __attribute__((unused))

typedef enum e_builtins
{
	e_cd,
	e_clear,
	e_echo,
	e_env,
	e_exec,
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
	int			shlvl;
	char		*cwd;
	char		*prev_cwd;
	char		*doc_wd;
	char		*start_wd;
	char		*history_wd;
	char		*home_wd;
	char		*logname;
	char		**environ;
	t_dblist	*env_list;
	t_dblist	*tmp_list;
	t_status	status;
	char		**bltin_names;
	int			(*builtin_funcs[])(struct s_data *data, \
		char *arg, char **flag, int status);
}	t_data;

//		init.c
void	init_data(t_data *data, char **env);
int		init_cwd(t_data *data);
void	update_env_list(t_data *d, char **env);
void	init_builtins_data(t_data *d);

//		prompt.c
int		get_terminal_prompt(t_data *d);
int		execute_prompt(t_data *d, char *prompt);

//		builtins
int		cd(t_data *d, char *arg, char **flags, int status);
int		clear(t_data *d, char *arg, char **flags, int status);
int		echo(t_data *d, char *arg, char **flags, int status);
int		env(t_data *d, char *arg, char **flags, int has_prefix);
int		exec(t_data *d, char *arg, char **flags, int status);
int		custom_exit(t_data *data, char *arg, char **flags, int status);
int		export(t_data *d, char *arg, char **flags, int tmp_mem);
int		ls(t_data *d, char *arg, char **flags, int status);
int		man(t_data *d, char *arg, char **flags, int status);
int		pwd(t_data *d, char *arg, char **flags, int status);
int		unset(t_data *d, char *arg, char **flags, int status);

//		utils
void	update_environ(t_data *d);
char	*get_env_value(t_data *d, char *key);
void	update_env_list(t_data *d, char **env);
int		update_env_variables(t_data *d);
void	reorder_dblst(t_dblist *list);
int		set_key_value(t_data *d, t_dblist *list, char *key, char *value);
int		update_cwd(t_data *data);

//		signal
void	setup_signal(int is_waiting);

//		utils_parsing
char	*ft_remove_prefix(char *str, char *prefix);
char	*truncate_at_end(char *str, const char cut_letter);
char	*get_next_line(int fd);
char	*ft_str_mega_join(const char *a, const char *b, \
	const char *c, const char *d);
int		get_char_occurence(char *str, char c);
int		get_arr_len(void **arr);

//		utils_parsing_2
int		handle_splits(t_data *d, char *prompt);
char	**get_flags(t_data *d, char *prmpt, char **cmd_name, char **arg);

//		utils_design
void	set_string_color(char **str, char *color);
int		write_anim_txt(t_data *d, const char *txt, int intrv, int exit_w);
int		is_same_string(char *a, char *b);

//		env
int		update_env_variables(t_data *d);
void	update_environ(t_data *d);

//		STRSTR
char	**ft_split_str(char *str, char *sep);
char	*ft_strstr(char *str, char *to_find);
char	*remove_char(char **txt, char c);

//		free
int		safe_free(void *item);
int		free_void_array(void ***item);
int		free_data(t_data *data);

//		write
int		write_at_rel_path(t_data *d, char *content, char *file_name);
int		write_at_abs_path(char *content, char *path, int flags);

#endif