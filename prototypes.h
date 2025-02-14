#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "header.h"

//		init/init.c
char		*custom_get_cwd(t_data *d);
int			update_cwd(t_data *data);
void		init_data(t_data *data, char **env);

//		init/init_bltn.c
void		export_usefull_var(t_data *d);
void		init_builtins_data(t_data *d);

//		pipe_parse/parse_heredoc.c
char		*parse_heredoc(char *end, t_data *d, char *print);

//		pipe_parse/fds.c
int			get_fd(t_data *d, char *file_path, t_tktype r_type);
void		save_original_fds(t_data *d);
void		close_redir_stream(t_data *d);

//		pipe_parse/pipe.c
t_token		*handle_pipe(t_data *d, t_token *cmd_in);

//		pipe_parse/redir_tools.c
char		*get_fd_content(t_data *d, int fd);
t_token		*redirect_pipe(t_data *d, t_token *nxt, int pipefd[2], int redir);
t_token		*skip_type(t_token *tok, t_tktype type_to_skip);
t_token		*get_next_redir(t_token *d);

//		pipe_parse/redir.c
void		handle_redir_out(t_data *d, t_token *cmd, char *arg, char **flags);
void		handle_redir_app(t_data *d, t_token *cmd, char *arg, char **flags);
void		handle_redir_in(t_data *d, t_token *cmd, char *arg, char **flags);
void		handle_redir_heredoc(t_data *d, t_token *cmd, char *arg, char **flags);
t_token		*handle_redir_cmd(t_data *d, t_token *cmd, char *arg, char **flags);

//		pipe_parse/heredoc.c
void		exec_heredoc(char *nd, char *print, int heredoc_fd);
int			ft_heredoc(char *end, t_data *d, char *print);

//		utils/string_tools3.c
char		*ms_strjoin(t_data *d, char const *s1, char const *s2);
char		*ms_strdup(t_data *d, const char *s1);
void		*ms_malloc(t_data *d, ssize_t size);
int			is_all_digit(char *str);
int			get_char_index(char *str, char c);

//		utils/string_tools.c
char		*ft_remove_prefix(t_data *d, const char *str, char *prefix);
char		*truncate_at_end(const char *str, char cut_letter);
char		*ft_str_mega_join(const char *a, const char *b, \
const char *c, const char d);
int			chr_amnt(const char *str, char c);
int			get_arr_len(void **arr);

//		utils/env_tools.c
void		update_environ(t_data *d);
char		*get_env_value(t_data *d, t_dblist *list, char *key);
void		update_env_var(t_data *d, t_dblist *list, char **var, char *key);
int			update_env_variables(t_data *d);
int			set_key_value(t_data *d, t_dblist *list, char *key, char *value);

//		utils/string_tools4.c
char		*ft_strstr(char *str, char *to_find);
char		**ft_split_str(t_data *d, char *str, char *sep);
int			char_in_str(char c, const char *txt);

//		utils/design_tools.c
void		set_string_color(char **str, char *color);
void		reset_readline(void);
int			is_directory(const char *path);

//		utils/write_tools.c
char		*replace_str(t_data *d, char *str, char *remove, char *replace);
char		*read_file(t_data *d, int fd);
int			is_builtin_cmd(t_data *d, char *str);
void		reverse_str_array(char **arr, int size);
void		remove_quotes(t_data *d, char **str);

//		utils/list_tools.c
t_dblist  *get_dblst_node(t_dblist *lst, const char *content);
void		add_to_list(t_data *d, t_dblist *lst, char *content);
char		**get_base_env(t_data *d);
void		init_env_list(t_data *d, char **env);
void		reorder_dblst(t_dblist *list);

//		utils/debug.c
void		show_exec_info(t_data *d, t_token *node, char *arg, char **flg);
void		show_token_info(t_data *d, t_token *node, char *prefix, char *suffix);
void		show_tokens_info(t_data *d, t_token *node, char *prfx, char *suffix);
void		show_cmd_status(t_data *d, t_token *node);

//		utils/free.c
int			safe_free(void *item);
int			free_void_array(void ***item);
int			free_data(t_data *data);

//		utils/string_tools2.c
int			is_in_quote(char *str, int index);
char		*copy_until_char(t_data *d, char *str, int *start, const char *set);
void		remove_chars(t_data *d, char **txt, const char *to_remove);
char		*contract_str(t_data *d, char **strs);
int			cmp_str(const char *a, const char *b);

//		builtins/ls.c
DIR			*get_directory(t_data *d, char *arg);
void		display_entry(struct dirent *entry, int *len);
int			execute_ls(t_data *d, char *arg, int print_arg, int error_if_dir);
int			ls(t_data *d, char *arg, char **flags, int status);

//		builtins/exec.c
int			handle_parent_process(pid_t child_pid);
int			exec(t_data *d, char *prg, char **argv, int is_indirect);

//		builtins/exit.c
int			custom_exit(t_data *data, char *error_msg, char **flags, int status);

//		builtins/cat.c
int			exec_cat(t_data *d, char *file_name);
int			cat(t_data *d, char *arg, char **flags, int status);

//		builtins/unset.c
int			unset(t_data *d, char *arg, char **flags, int status);

//		builtins/env.c
int			env(t_data *d, char *arg, char **flags, int has_prefix);

//		builtins/pwd.c
int			pwd(t_data *d, char *arg, char **flags, int status);

//		builtins/clear.c
int			clear(t_data *d, char *a, char **f, int st);

//		builtins/export.c
int			export(t_data *d, char *arg, char **flags, int tmp_mem);

//		builtins/cd.c
int			cd(t_data *d, char *arg, char **flags, int status);

//		builtins/doc.c
int			doc(t_data *d, char *arg, char **flags, int status);

//		builtins/exec_utils.c
char		**set_argv(t_data *d, char *prog_name);
char		*get_dir_in_path(t_data *d, char *cmd_name);
char		*handle_path_in_dir(t_data *d, char *prg, int is_indirect);
int			is_valid_exec_file(const char *file);
int			increment_shlvl(t_data *d);

//		builtins/echo.c
int			echo(t_data *d, char *arg, char **flags, int status);

//		prompt/prompt_execute.c
int			handle_direct_exec(t_data *d, char *cmd_name, char *arg, char **flags);
int			execute_command(t_data *d, char *cmd_name, char *arg, char **flags);

//		prompt/prompt_checker.c
char		*get_quote_end(t_data *d, char *end, char *msg);
int			set_quotes(t_data *d, char **prompt);
int			set_pipe(t_data *d, char **prmpt);
int			set_par(t_data *d, char **prmpt, int i);
int			validate_prmpt(t_data *d, char **prmpt);

//		prompt/prompt.c
char		*solo_pipe(t_data *d, char *trm_line);
int			get_terminal_prompt(t_data *d);

//		prompt/prompt_checker2.c
int			is_valid_redir(char *p, int i, int j, char c);
int			check_redir_validity(char *prompt);
int			check_pipe_validity(t_data *d, char **prmpt, int last_pipe_index);
int			validate_prmpt_b(char **prmpt, int has_redir, int is_only_spc);

//		signal.c
void		setup_signal(int is_waiting, int is_heredoc);

//		tokens/token_execute2.c
t_token		*set_args(t_data *d, t_token *cmd, t_token *arg_token, char ***flags);
t_token		*setup_args(t_data *d, char **arg, t_token *cmd, char ***flags);
int			validate_redir(t_token *redir);
t_token		*handle_command_token(t_data *d, t_token *node, int should_redir);

//		tokens/token_execute.c
t_token		*handle_logical_token(t_data *d, t_token *node);
t_token		*handle_token(t_data *d, t_token *node);
int			exec_prompt(t_data *d, char *terminal_line);

//		tokens/utils_tokens.c
char		*get_new_split(char *str, int *i);
char		**split_prompt(t_data *d, char *str);
void		unquote_splits(t_data *d, char **splits);
t_token		*get_next_token(t_token *token, t_tktype type, int stops_at_same);
void		link_token_pipes(t_token *tokens);

//		tokens/token_parser2.c
int			requires_arg(t_token *node);
int			validate_token(t_data *d, t_token *node);
void		split_list(t_token *source, t_token **front_ref, t_token **back_ref);
t_token		*merge_sorted_lists(t_token *a, t_token *b);
void		merge_sort_tokens(t_token **head_ref);

//		tokens/token_expand_tools.c
char		*expand_special_segment(t_data *d, char *split, int *i);
char		*expand_segment(t_data *d, char *split, int *i);
char		*expand_split(t_data *d, char *split, int len, int i);
void		expand_splits(t_data *d, char **splits);
void		update_node_expansion(t_data *d, t_token *node, int set_new_type);

//		tokens/token_parser.c
t_tktype	get_token_type(t_data *d, int *was_cmd, char *str, t_token *prev);
t_token		*tokenize_string(t_data *d, char *prompt);
char		*expand_home_token(t_data *d, char *cmd_name);

//		tokens/tokens.c
t_token		*new_token(char *name, t_token *prv, t_tktype type, int par);
t_token		*token_first(t_token *lst);
t_token		*get_token(t_token *lst, char *name);
void		clear_tokens(t_token *token);
void		remove_token(t_token *token);

//		minishell.c
char		*get_last_line(t_data *d, const char *filename);

#endif
