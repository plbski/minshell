/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:04:55 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/04 13:19:57 by giuliovalen      ###   ########.fr       */
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
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# define START_ANIM_TEXT "			\033[31m~~~ \033[35mMinishell \033[31mby \
\033[34mgvlente \033[31m& \033[34mpbuet\033[31m ~~~ \033[0m"
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
# define GREY "\033[38;5;240m"
# define LIGHT_GREY "\033[38;5;250m"

# define PROMPT_LOGNAME_COL 	CYAN
# define PROMPT_CWD_COL			YELLOW

# define CMD_NOT_FOUND	127
# define FCT_SUCCESS	0
# define FCT_FAIL		1
# define EXIT_CHILD		-1

int	g_quit_in_heredoc;

typedef enum e_token_type
{
	tk_command,
	tk_argument,
	tk_expand_arg,
	tk_red_in,
	tk_red_out,
	tk_red_app,
	tk_hered,
	tk_pipe,
	tk_logical,
	tk_quote,
	tk_dbquote,
	tk_wildcard,
	tk_flag,
	tk_exec,
}	t_toktype;

typedef enum e_builtins
{
	e_cat,
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
	e_unset,
}	t_builtins_types;

typedef enum e_redir_type
{
	APPEND,
	OUT,
	IN,
	REDIR_HEREDOC,
}	t_redir_type;

typedef struct s_data
{
	int			fd;
	int			pipefd;
	int			debug_mode;
	int			shlvl;
	int			last_exit_status;
	int			last_cmd_status;
	char		*cwd;
	char		*prev_cwd;
	char		*man_wd;
	char		*start_wd;
	char		*history_wd;
	char		*home_wd;
	char		*logname;
	char		**environ;
	const char	**types_names;
	t_dblist	*env_list;
	t_dblist	*tmp_list;
	char		**bltin_names;
	int			(*blt_fct[12])(struct s_data *d, char *arg, char **flg, int s);
}	t_data;

typedef struct s_token
{
	char			*name;
	t_toktype		type;
	struct s_token	*prv;
	struct s_token	*next;
	struct s_token	*pipe_out;
	int				par;
	int				(*fct)(struct s_data *d, char *arg, char **flg, int s);
}	t_token;

typedef struct s_tk_pipe
{
	t_token	*in;
	t_token	*out;
	int		pid;
	int		fd[2];
}	t_tk_pipe;

//		pipe_parse/pipe.c
t_token		*get_pipe_output(t_token *input);
t_token		*handle_pipe(t_data *d, t_token *cmd);

//		pipe_parse/redir.c
void		create_file(t_data *d, char *file_name, t_toktype r_type);
t_token		*handle_redir_token(t_data *d, t_token *redir_node, t_toktype type);
void		close_redir_stream(t_data *d);

//		pipe_parse/heredoc.c
char		*heredoc(char *end, t_data *d, char *print, int is_quote);

//		init.c
char		*custom_get_cwd(t_data *d);
int			update_cwd(t_data *data);
void		init_data(t_data *data, char **env);

//		utils/string_tools.c
char		*ft_remove_prefix(t_data *d, const char *str, char *prefix);
char		*truncate_at_end(const char *str, char cut_letter);
char		*ft_str_mega_join(const char *a, const char *b, \
	const char *c, const char *d);
int			chr_amnt(const char *str, char c);
int			get_arr_len(void **arr);

//		utils/string_tools2.c
int			is_in_quote(char *str, int index);
char		*copy_until_char(t_data *d, char *str, int *start, const char *set);
void		remove_chars(t_data *d, char **txt, const char *to_remove);
char		*contract_str(t_data *d, char **strs);
int			cmp_str(const char *a, const char *b);

//		utils/string_tools3.c
char		*ms_strjoin(t_data *d, char const *s1, char const *s2);
char		*ms_strdup(t_data *d, const char *s1);
void		*ms_malloc(t_data *d, ssize_t size);
int			is_all_digit(char *str);
int			get_char_index(char *str, char c);

//		utils/string_tools4.c
char		*ft_strstr(char *str, char *to_find);
char		**ft_split_str(t_data *d, char *str, char *sep);
int			char_in_str(char c, const char *txt);

//		utils/write_tools.c
int			write_at_abs_path(char *content, char *path, int flags);
int			write_at_rel_path(t_data *d, char *content, char *file_name);
char		*replace_str(t_data *d, char *str, char *remove, char *replace);
char		*read_file(t_data *d, int fd);

//		utils/env_tools.c
void		update_environ(t_data *d);
char		*get_env_value(t_data *d, t_dblist *list, char *key);
int			update_env_variables(t_data *d);
int			set_key_value(t_data *d, t_dblist *list, char *key, char *value);

//		utils/prompt_checker.c
char		*get_quote_end(t_data *d, char *end, char *msg);
int			set_quotes(t_data *d, char **prompt);
int			set_pipe(t_data *d, char **prmpt);
int			set_par(t_data *d, char **prmpt, int i);
int			validate_prmpt(t_data *d, char **prmpt);

//		utils/list_tools.c
t_dblist	*get_dblst_node(t_dblist *lst, const char *content);
void		add_to_list(t_data *d, t_dblist *lst, char *content);
void		init_env_list(t_data *d, char **env);
void		reorder_dblst(t_dblist *list);

//		utils/debug.c
void		show_exec_info(t_data *d, t_token *node, char *arg, char **flg);
void		show_token_info(t_data *d, t_token *node, char *prfx, char *suffix);
void		show_tokens_info(t_data *d, t_token *node, char *prfx, char *suffix);
void		show_cmd_status(t_data *d, t_token *node);

//		utils/prompt_checker2.c
int			is_valid_redir(char *p, int i, int j, char c);
int			check_redir_validity(char *prompt);
int			check_pipe_validity(t_data *d, char **prmpt, int last_pipe_index);
int			validate_prmpt_b(char **prmpt, int has_redir, int is_only_spc);

//		prompt.c
int			get_terminal_prompt(t_data *d);

//		builtins
int			man(t_data *d, char *arg, char **flags, int status);
//		ls.c
DIR			*get_directory(t_data *d, char *arg);
void		display_entry(struct dirent *entry, int *len);
int			execute_ls(t_data *d, char *arg, int print_arg, int err_if_dir);
int			ls(t_data *d, char *arg, char **flags, int status);
int			custom_exit(t_data *data, char *error_msg, \
	char **flags, int status);
int			cd(t_data *d, char *arg, char **flags, int status);
int			clear(t_data *d, char *a, char **f, int st);
int			cat(t_data *d, char *arg, char **flags, int status);
int			echo(t_data *d, char *arg, char **flags, int status);
int			env(t_data *d, char *arg, char **flags, int has_prefix);
int			exec(t_data *d, char *program, char **argv, int u);
int			unset(t_data *d, char *arg, char **flags, int status);
int			pwd(t_data *d, char *arg, char **flags, int status);
int			export(t_data *d, char *arg, char **flags, int tmp_mem);

//		free.c
int			safe_free(void *item);
int			free_void_array(void ***item);
int			free_data(t_data *data);

//		parse_prompt.c
int			execute_command(t_data *d, char *cmd_name, char *arg, char **flags);

//		init_bltn.c
void		init_builtins_data(t_data *d);

//		signal.c
void		setup_signal(int is_waiting, int is_heredoc);

//		tokens/token_execute.c
t_token		*set_args(t_data *d, t_token *strt, t_toktype k_typ, char ***args);
t_token		*handle_command_token(t_data *d, t_token *node);
t_token		*handle_token(t_data *d, t_token *node);
int			exec_prompt(t_data *d, char *terminal_line);

//		tokens/utils_tokens.c
char		**split_prompt(t_data *d, char *str);
void		unquote_splits(t_data *d, char **splits);
t_token		*get_next_token(t_token *token, t_toktype type, int stops_at_same);
void		link_token_pipes(t_token *tokens);

//		tokens/token_expand_tools.c
char		*expand_special_segment(t_data *d, char *split, int *i);
char		*expand_segment(t_data *d, char *split, int *i);
char		*expand_split(t_data *d, char *split, int len, int i);
void		expand_splits(t_data *d, char **splits);
void		update_node_expansion(t_data *d, t_token *node, int set_new_type);

//		tokens/token_parser.c
t_toktype	get_token_type(t_data *d, char *str, t_token *prev);
int			requires_arg(t_token *node);
int			validate_token(t_data*d, t_token *node);
t_token		*tokenize_string(t_data *d, char *prompt);

//		tokens/tokens.c
t_token		*new_token(char *name, t_token *prv, t_toktype type, int par);
t_token		*token_first(t_token *lst);
t_token		*get_token(t_token *lst, char *name);
void		clear_tokens(t_token *token);
void		remove_token(t_token *token);
void		merge_sort_tokens(t_token **head_ref);

void		reset_readline(void);
char		*get_next_line(int fd);
int			handle_direct_exec(t_data *d, char *cmd_name, \
	char *arg, char **flags);
int			is_directory(const char *path);

#endif