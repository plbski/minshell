.SILENT:

MINISHELL_NAME = minishell
TEST_PRG_NAME = test

MINISHELL_PRG_SRC = c_files/minishell.c
MINISHELL_SRC = \
c_files/init/init.c c_files/init/init_bltn.c c_files/tools/str_tools/write_tools.c c_files/tools/str_tools/strget_tools.c \
c_files/tools/str_tools/splitstr_tools.c c_files/tools/str_tools/strcmp_tools.c c_files/tools/str_tools/strmod_tools.c \
c_files/tools/var/env_tools.c c_files/tools/var/quote_tools.c c_files/tools/var/var_tools.c c_files/tools/var/free_tools.c \
c_files/tools/var/list_tools.c c_files/tools/debug.c c_files/tools/signal.c c_files/input/input_check.c \
c_files/input/input_execute.c c_files/input/input_split.c c_files/input/input.c c_files/input/input_checkb.c \
c_files/redirection/parse_heredoc.c c_files/redirection/fds.c c_files/redirection/pipe.c c_files/redirection/redir_tools.c \
c_files/redirection/redir.c c_files/redirection/heredoc.c c_files/builtins/ls.c c_files/builtins/exec.c \
c_files/builtins/exit.c c_files/builtins/unset.c c_files/builtins/env.c c_files/builtins/pwd.c c_files/builtins/export.c \
c_files/builtins/cd.c c_files/builtins/doc.c c_files/builtins/exec_utils.c c_files/builtins/echo.c c_files/tokens/token_parse2.c \
c_files/tokens/token_parse.c c_files/tokens/token_exec.c c_files/tokens/utils_tokens.c c_files/tokens/token_expand.c \
c_files/tokens/tokens.c c_files/input/input_substitute.c c_files/input/subshell.c c_files/tokens/token_execute_utils.c \
c_files/input/subshell_solve.c

LIBFT_DIR = libft/
DPRINTF_DIR = dprintf/
GNL_DIR = gnl/
LISTS_DIR = lists/
TEST_PRG_DIR = test_programs/

GNL = $(GNL_DIR)get_next_line.a
DPRINTF = $(DPRINTF_DIR)printf.a
LISTS = $(LISTS_DIR)lists.a
LIBFT = $(LIBFT_DIR)libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

GREEN = 	\033[0;32m
BLUE = 		\033[34m
MAGENTA = 	\033[35m
CYAN = 		\033[36m
RESET = 	\033[0m

$(MINISHELL_NAME): $(MINISHELL_SRC) $(MINISHELL_PRG_SRC) $(LIBFT) $(GNL) $(DPRINTF) $(LISTS)
	make -C $(TEST_PRG_DIR) --no-print-directory re
	$(CC) $(CFLAGS) $(MINISHELL_SRC) $(MINISHELL_PRG_SRC) -L$(LIBFT_DIR) $(GNL) $(DPRINTF) $(LISTS) -lft -DNO_COLOR -o $(MINISHELL_NAME) $(LDFLAGS)
	@echo "$(MAGENTA)$(MINISHELL_NAME) successfully built.$(RESET)"

$(LIBFT):
	make -C $(LIBFT_DIR) --no-print-directory

$(DPRINTF):
	make -C $(DPRINTF_DIR) --no-print-directory

$(GNL):
	make -C $(GNL_DIR) --no-print-directory

$(LISTS):
	make -C $(LISTS_DIR) --no-print-directory

all: $(MINISHELL_NAME)

debug: $(MINISHELL_NAME) $(MINISHELL_SRC) $(MINISHELL_PRG_SRC) $(LIBFT) $(DPRINTF) $(GNL) $(LISTS)
	make -C $(TEST_PRG_DIR) --no-print-directory re
	$(CC) $(CFLAGS) -fsanitize=address -g $(MINISHELL_SRC) $(MINISHELL_PRG_SRC) -L$(LIBFT_DIR) $(GNL) $(DPRINTF) $(LISTS) -lft -o $(MINISHELL_NAME) $(LDFLAGS)
	@echo "$(MAGENTA)$(MINISHELL_NAME) -fsan successfully built.$(RESET)"

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions=a.supp --log-file="leaks.log" ./minishell

leaks: re
	leaks --atExit -- ./minishell

clean:
	make -C $(LIBFT_DIR) --no-print-directory clean
	make -C $(DPRINTF_DIR) --no-print-directory clean
	make -C $(LISTS_DIR) --no-print-directory clean
	make -C $(GNL_DIR) --no-print-directory clean
	make -C $(TEST_PRG_DIR) --no-print-directory clean
	rm -f $(MINISHELL_NAME)

fclean: clean
	make -C $(LIBFT_DIR) --no-print-directory fclean QUIET=1
	make -C $(DPRINTF_DIR) --no-print-directory fclean QUIET=1
	make -C $(LISTS_DIR) --no-print-directory fclean QUIET=1
	make -C $(GNL_DIR) --no-print-directory fclean QUIET=1

re: fclean all

phony: all clean fclean re
