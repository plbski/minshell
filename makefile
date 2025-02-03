.SILENT:

MINISHELL_NAME = minishell
TEST_PRG_NAME = test

MINISHELL_PRG_SRC = c_files/minishell.c
MINISHELL_SRC = \
c_files/init/init.c c_files/init/init_bltn.c c_files/pipe_parse/pipe.c c_files/pipe_parse/redir.c c_files/pipe_parse/heredoc.c \
c_files/utils/string_tools3.c c_files/utils/string_tools.c c_files/utils/string_tools4.c c_files/utils/env_tools.c \
c_files/utils/design_tools.c c_files/utils/list_tools.c c_files/utils/debug.c c_files/utils/free.c c_files/utils/string_tools2.c \
c_files/builtins/man.c c_files/builtins/ls.c c_files/builtins/exec.c c_files/builtins/exit.c c_files/builtins/unset.c \
c_files/builtins/env.c c_files/builtins/pwd.c c_files/builtins/clear.c c_files/builtins/export.c c_files/builtins/cd.c \
c_files/builtins/echo.c c_files/prompt/prompt_execute.c c_files/prompt/prompt_checker.c c_files/prompt/prompt.c \
c_files/prompt/prompt_checker2.c c_files/signal.c c_files/tokens/token_execute.c c_files/tokens/utils_tokens.c \
c_files/tokens/token_parser2.c c_files/tokens/token_expand_tools.c c_files/tokens/token_parser.c c_files/tokens/tokens.c \
c_files/utils/write_tools.c c_files/builtins/cat.c

TEST_PRG_SRC = test_program.c

LIBFT_DIR = libft/
GNL_DIR = gnl/
LISTS_DIR = lists/

GNL = $(GNL_DIR)get_next_line.a
LISTS = $(LISTS_DIR)lists.a
LIBFT = $(LIBFT_DIR)libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

GREEN = 	\033[0;32m
BLUE = 		\033[34m
MAGENTA = 	\033[35m
CYAN = 		\033[36m
RESET = 	\033[0m

$(MINISHELL_NAME): $(MINISHELL_SRC) $(MINISHELL_PRG_SRC) $(LIBFT) $(GNL) $(LISTS)
	$(CC) $(CFLAGS) $(MINISHELL_SRC) $(MINISHELL_PRG_SRC) -L$(LIBFT_DIR) $(GNL) $(LISTS) -lft -o $(MINISHELL_NAME) $(LDFLAGS)
	@echo "$(MAGENTA)$(MINISHELL_NAME) successfully built.$(RESET)"

$(TEST_PRG_NAME): $(MINISHELL_SRC) $(TEST_PRG_SRC) $(LIBFT) $(GNL) $(LISTS)
	$(CC) $(CFLAGS) $(MINISHELL_SRC) $(TEST_PRG_SRC) -L$(LIBFT_DIR) $(GNL) $(LISTS) -lft -o $(TEST_PRG_NAME) $(LDFLAGS)
	@echo "$(MAGENTA)$(TEST_PRG_NAME) successfully built.$(RESET)"

$(LIBFT):
	make -C $(LIBFT_DIR) --no-print-directory

$(GNL):
	make -C $(GNL_DIR) --no-print-directory

$(LISTS):
	make -C $(LISTS_DIR) --no-print-directory

all: $(MINISHELL_NAME)

debug: $(MINISHELL_NAME) $(MINISHELL_SRC) $(MINISHELL_PRG_SRC) $(LIBFT) $(GNL) $(LISTS)
	$(CC) $(CFLAGS) -fsanitize=address -g $(MINISHELL_SRC) $(MINISHELL_PRG_SRC) -L$(LIBFT_DIR) $(GNL) $(LISTS) -lft -o $(MINISHELL_NAME) $(LDFLAGS)
	@echo "$(MAGENTA)$(MINISHELL_NAME) -fsan successfully built.$(RESET)"

clean:
	make -C $(LIBFT_DIR) --no-print-directory clean
	make -C $(GNL_DIR) --no-print-directory clean
	make -C $(LISTS_DIR) --no-print-directory clean
	rm -f $(MINISHELL_NAME)

fclean: clean
	make -C $(LIBFT_DIR) --no-print-directory fclean
	make -C $(LISTS_DIR) --no-print-directory fclean
	make -C $(GNL_DIR) --no-print-directory fclean

re: fclean all

phony: all clean fclean re
