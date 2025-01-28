/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:04:55 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/28 15:53:31 by giuliovalen      ###   ########.fr       */
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

# define FCT_SUCCESS		0
# define FCT_FAIL		1

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
	int			last_exit_status;
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
	int			(*builtin_funcs[11])(struct s_data *data, \
		char *arg, char **flag, int status);
}	t_data;

//		init.c
void		init_data(t_data *data, char **env);
void		init_builtins_data(t_data *d);
void		init_env_list(t_data *d, char **env);

//		prompt.c
int			get_terminal_prompt(t_data *d);
int			execute_prompt(t_data *d, char *prompt);

//		builtins
int			cd(t_data *d, char *arg, char **flags, int status);
int			clear(t_data *d, char *arg, char **flags, int status);
int			echo(t_data *d, char *arg, char **flags, int status);
int			env(t_data *d, char *arg, char **flags, int has_prefix);
int			exec(t_data *d, char *arg, char **flags, int status);
int			custom_exit(t_data *data, char *arg, char **flags, int status);
int			export(t_data *d, char *arg, char **flags, int tmp_mem);
int			ls(t_data *d, char *arg, char **flags, int status);
int			man(t_data *d, char *arg, char **flags, int status);
int			pwd(t_data *d, char *arg, char **flags, int status);
int			unset(t_data *d, char *arg, char **flags, int status);

//		env_tools
void		update_environ(t_data *d);
char		*get_env_value(t_data *d, t_dblist *lst, char *key);
int			update_env_variables(t_data *d);
int			set_key_value(t_data *d, t_dblist *list, char *key, char *value);

//		list_tools
t_dblist	*get_dblst_node(t_dblist *lst, const char *content);
void		add_to_list(t_data *d, t_dblist *lst, char *content);
void		reorder_dblst(t_dblist *list);

//		utils
int			update_cwd(t_data *data);
char		**get_splits(t_data *d, char *prmpt, char **cmd_name, char **arg);

//		string_tools
char		*ft_remove_prefix(const char *str, char *prefix);
char		*truncate_at_end(const char *str, char cut_letter);
char		*ft_str_mega_join(const char *a, const char *b, \
	const char *c, const char *d);
int			get_char_occurence(const char *str, char c);
int			get_arr_len(void **arr);

//		string_tools_2
int			is_in_quote(char *str, int index);
char		*copy_until_char(t_data *d, char *str, int *start, const char *set);
char		*remove_chars(char *txt, const char *to_remove);
char		*contract_str(t_data *d, char **strs);
int			is_same_string(const char *a, const char *b);

//		signal
void		setup_signal(int is_waiting);

//		utils_parsing_2
int			handle_splits(t_data *d, char *prompt);
char		**get_flags(t_data *d, char *prmpt, char **cmd_name, char **arg);
int			is_valid_prompt(char *prompt);

//		utils_design
void		set_string_color(char **str, char *color);
int			write_anim_txt(t_data *d, const char *txt, int intrv, int exit_w);

//		token_expand_tools
void		expand_splits(t_data *d, char **splits);

int			handle_direct_exec(t_data *d, char *cmd_name, char *arg, char **flags);

//		STRSTR
char		**ft_split_str(char *str, char *sep);
char		*ft_strstr(char *str, char *to_find);
int			ft_char_in_str(char c, const char *txt);

//		free
int			safe_free(void *item);
int			free_void_array(void ***item);
int			free_data(t_data *data);

//		write
int			write_at_rel_path(t_data *d, char *content, char *file_name);
int			write_at_abs_path(char *content, char *path, int flags);

//		gnl
char		*get_next_line(int fd);

//		debug
char		*get_dir_in_path(t_data *d, char *cmd_name);
int			search_true_cmd(t_data *d, char *cmd_name, char *arg, char **flags);

#endif