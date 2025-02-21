/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:04:55 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/21 20:03:07 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include "msh_style.h"
# include "libft/libft.h"
# include "lists/lists.h"
# include "dprintf/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <sys/ioctl.h>

# define ERR_NOT_FOUND 	2
# define ERR_NOT_EXEC 	1
# define ERR_IS_DIR		0

# define CMD_NOT_FOUND	127
# define CMD_NOT_EXEC	126
# define CMD_IS_DIR		126

# define EMPTY_FILE		5
# define FCT_OK	0
# define FCT_FAIL		1
# define EXIT_CHILD		-1

typedef enum e_token_type
{
	tk_cmd,
	tk_arg,
	tk_red_in,
	tk_red_out,
	tk_red_app,
	tk_hered,
	tk_pipe,
	tk_logical,
	tk_wildcard,
}	t_tktype;

typedef enum e_builtins
{
	e_cd,
	e_echo,
	e_ls,
	e_env,
	e_exec,
	e_exit,
	e_export,
	e_doc,
	e_pwd,
	e_unset,
	e_source,
}	t_builtins_types;

typedef struct s_token
{
	char			*name;
	t_tktype		type;
	struct s_token	*prv;
	struct s_token	*next;
	struct s_token	*pipe_out;
	struct s_token	*subsh_out;
	struct s_token	*redir;
	struct s_token	*red_arg;
	struct s_token	*nxt_eval;
	int				is_cmd_subst;
	int				is_rd;
	int				par;
}	t_token;

typedef struct s_data
{
	struct termios	oldt;
	t_dblist		*env_list;
	t_dblist		*tmp_list;
	t_dblist		*var_list;
	char			**bltin_names;
	const char		**types_names;
	char			**environ;
	char			*cwd;
	char			*prev_cwd;
	char			*man_wd;
	char			*history_wd;
	char			*heredoc_wd;
	char			*home_wd;
	char			*start_wd;
	char			*msh_wd;
	char			*logname;
	int				subsh_fd;
	char			*prv_input;
	int				trunc_input;
	int				base_stdin;
	int				base_stdout;
	int				saved_stdin;
	int				saved_stdout;
	int				debug_mode;
	int				shlvl;
	int				heredocfd;
	int				last_exit;
	int				brackets;
	int				fork_child;
	int				var;
	int				(*blt_fct[11])(struct s_data *d, char *a, char **f, int s);
}	t_data;

extern int	g_quit_in_heredoc;

//		init/init.c
char		*custom_get_cwd(t_data *d);
int			update_cwd(t_data *data);
void		init_msh_data(t_data *data, char *path, char **env);

//		init/init_bltn.c
void		export_usefull_var(t_data *d);
void		init_builtins_data(t_data *d);

//		tools/str_tools/write_tools.c
int			is_builtin_cmd(t_data *d, char *str);
int			is_all_digit(char *str);
int			get_char_index(char *str, char c);
char		*get_fd_content(t_data *d, int fd);

//		tools/str_tools/strget_tools.c
char		*ms_strjoin(t_data *d, char const *s1, char const *s2);
char		*ms_strdup(t_data *d, const char *s1);
void		*ms_malloc(t_data *d, ssize_t size);
void		*ms_realloc(t_data *d, void *ptr, size_t new_size);
char		*char_join(char a, char b, char c, char d);

//		tools/str_tools/splitstr_tools.c
char		*ft_strstr(const char *str, const char *to_find);
char		**ft_split_str(t_data *d, char *str, char *sep);
char		*contract_str(t_data *d, char **strs);

//		tools/strinsert.c
char		*str_insert(const char *str, int rmv_start, \
	int rmv_end, const char *new_str);
void		replace_strstr(t_data *d, char **str, \
		const char *remove, const char *replace);

//		tools/str_tools/strcmp_tools.c
int			same_str(const char *a, const char *b);
int			char_in_str(char c, const char *txt);
int			chr_amnt(const char *str, char c);
int			get_arr_len(void **arr);
int			ft_strcmp(const char *s1, const char *s2);

//		tools/str_tools/strmod_tools.c
char		*ms_rem_prefix(t_data *d, char **str, const char *prfx, int alloc);
char		*truncate_at_end(const char *str, char cut_letter);
char		*ft_megajoin(const char *a, const char *b, \
		const char *c, const char *d);
char		*copy_until_char(t_data *d, char *str, int *start, const char *set);
void		remove_chars(t_data *d, char **txt, const char *to_remove);

//		tools/var/env_tools.c
void		update_environ(t_data *d);
char		*get_env_value(t_data *d, t_dblist *list, char *key);
void		update_env_var(t_data *d, t_dblist *list, char **var, char *key);
int			update_env_variables(t_data *d);
int			set_key_value(t_data *d, t_dblist *list, char *key, char *value);

//		tools/var/quote_tools.c
int			is_only_quotes(char *str);
void		remove_quotes(t_data *d, char **str);
int			in_quote(char *str, int index);

//		tools/var/var_tools.c
void		reset_readline(void);
int			is_directory(const char *path);
void		setstr(t_data *d, char **str, char *new);
char		**ms_split(t_data *d, const char *str, char remove);
void		ms_substr(t_data *d, char **s, unsigned int start, size_t len);

//		tools/var/free_tools.c
int			safe_free(void *item);
int			free_void_array(void ***item);
int			free_data(t_data *data);

//		tools/var/list_tools.c
t_dblist	*get_dblst_node(t_dblist *lst, const char *content);
char		**get_base_env(t_data *d);
void		init_env_list(t_data *d, char **env);
void		reorder_dblst(t_dblist *list);

//		tools/debug.c
void		show_exec_info(t_data *d, t_token *node, char *arg, char **flg);
t_token		*show_token_info(t_data *d, t_token *node, char *prx, int spacing);
void		show_tokens_info(t_data *d, t_token *start, char *prfx, int i);
void		show_cmd_status(t_data *d, t_token *node);
void		show_char_array(char *arr_name, char **arr);

//		tools/signal.c
void		setup_signal(int is_waiting, int is_heredoc);

//		input/input_check.c
int			validate_input(t_data *d, char **input);

//		input/input_execute.c
int			handle_direct_exec(t_data *d, char *cmd, char *arg, char **flg);
int			execute_command(t_data *d, char *cmd_name, char *arg, char **flags);
int			exec_input(t_data *d, char *input);

//		input/input_split.c
char		*get_token_in_split(t_data *d, char *str, int *i);
char		*get_new_split(t_data *d, char *str, int *i);
char		**split_input(t_data *d, char *input);
void		unquote_splits(t_data *d, char **splits);

//		input/input.c
int			process_input(t_data *d, int start);

//		input/input_checkb.c
int			only_space(char *str);
int			set_pipe(t_data *d, char **input);
int			check_redir_validity(char *input);

//		redirection/parse_heredoc.c
char		*parse_heredoc(char *end, t_data *d, char *print);

//		redirection/fds.c
int			get_fd(t_data *d, char *file_path, t_tktype r_type);
void		save_stds(t_data *d);
void		reset_redir(t_data *d);
void		restore_fds(t_data *d);

//		redirection/pipe.c
t_token		*pipe_handler(t_data *d, t_token *cmd_in);

//		redirection/redir_tools.c
t_token		*redirect_pipe(t_data *d, t_token *nxt, int pipefd[2], int redir);
t_token		*skip_type(t_token *tok, t_tktype type_to_skip);
t_token		*get_next_redir(t_token *d);

//		redirection/redir.c
void		handle_hered_redir(t_data *d, t_token *hered_arg);
t_token		*handle_redir_cmd(t_data *d, t_token *cmd, char *arg, char **flags);

//		redirection/heredoc.c
int			exec_heredoc(char *nd, char *print, int heredoc_fd);
int			ft_heredoc(char *end, t_data *d, char *print);

//		builtins/ls.c
DIR			*get_directory(t_data *d, char *arg);
int			ls(t_data *d, char *arg, char **flags, int status);

//		builtins
int			exec(t_data *d, char *prg, char **argv, int is_indirect);
int			custom_exit(t_data *data, char *error_msg, char **flags, int stats);
int			unset(t_data *d, char *arg, char **flags, int status);
int			env(t_data *d, char *arg, char **flags, int has_prefix);
int			pwd(t_data *d, char *arg, char **flags, int status);
int			export(t_data *d, char *arg, char **flags, int tmp_mem);
int			cd(t_data *d, char *arg, char **flags, int status);
int			doc(t_data *d, char *arg, char **flags, int status);
int			echo(t_data *d, char *arg, char **flags, int status);
int			source(t_data *d, char *arg, char **flags, int status);

//		builtins/exec_utils.c
char		**set_argv(t_data *d, char *prog_name, char **args, int args_len);
char		*get_path_in_env(t_data *d, char *prg, int is_exec, int *fct_ret);
int			valid_exec(const char *file, int *ret, int exc, int pr);
void		print_exec_error(const char *arg, int st, int exex);

//		tokens/token_parse.c
t_tktype	get_token_type(t_token *prv_cmd, char *str);
t_token		*tokenize_string(t_data *d, char *prompt);
t_token		*get_next_redir(t_token *d);
void		set_redir_args(t_token *tok);
int			requires_arg(t_token *node);
int			is_valid_identifier(char *arg);

//		tokens/token_execute.c
t_token		*handle_command_token(t_data *d, t_token *node, int should_redir);
t_token		*setup_args(t_data *d, char **arg, t_token *cmd, char ***flags);
t_token		*consumate_heredoc(t_data *d, t_token *cmd, char *arg, char **flg);
int			validate_redir(t_data *d, t_token *redir);

//		tokens/utils_tokens.c
t_token		*get_next_token(t_token *token, t_tktype type, int stops_at_same);
void		link_token_pipes(t_token *tokens);

//		tokens/token_expand.c
char		*expand_special_segment(t_data *d, char *split, int *i);
char		*expand_segment(t_data *d, char *split, int *i);
char		*expand_split(t_data *d, char *split, int len, int i);
void		expand_splits(t_data *d, char **splits);
void		update_node_expansion(t_data *d, t_token *node);

//		tokens/tokens.c
t_token		*new_token(char *name, t_token *prv, t_tktype type, int parth_ordr);
t_token		*token_first(t_token *lst);
t_token		*get_token(t_token *lst, char *name);
void		clear_tokens(t_token *token);
void		remove_token(t_token *token);

//		minishell.c
char		*get_last_line(t_data *d, const char *filename);

char		*get_next_line(int fd);
void		set_nonblocking_mode(int enable, struct termios *saved);
void		set_parenthesis_rdections(t_token *tok);
t_token		*get_last_arg(t_token *cmd);

//		subst.c
char		*get_cmd_subst(t_data *d, char *str, int *i, char *ret_cmd);
void		solve_cmd_substitutes(t_data *d, char ***spl);

//		subshell.c
void		set_subshells(t_data *d, t_token *tokens);
void		iterate_tokens(t_data *d, t_token *node);
t_token		*solve_subshell(t_data *d, t_token *start);
char		*ms_strndup(t_data *d, const char	*s1, ssize_t n);
char		*ft_strndup(const char	*s1, ssize_t n);

char		*get_rc_path(t_data *d);
void		set_strarr(char ***to_replace, char **new_arr);
void		swap_redir_cmd(t_data *d, t_token *node);
void		swap_tokens(t_token *a, t_token *b);
void		reorder_misplaced_redirs(t_data *d, t_token *start);
t_token		*handle_mult_redirs(t_data *d, t_token *cmd, char *arg, char **flags);

#endif