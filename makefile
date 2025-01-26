.SILENT:

MINISHELL_NAME = minishell
MINISHELL_SRC = \
c_files/init.c c_files/utils/env_handler.c c_files/utils/strstr.c c_files/utils/utils_design.c \
c_files/utils/utils_parsing.c c_files/prompt.c c_files/builtins/man.c c_files/builtins/ls.c c_files/builtins/exit.c \
c_files/builtins/unset.c c_files/builtins/env.c c_files/builtins/pwd.c c_files/builtins/clear.c c_files/builtins/export.c \
c_files/builtins/cd.c c_files/builtins/echo.c c_files/free.c c_files/signal.c c_files/minishell.c c_files/builtins/exec.c \
c_files/init_builtins.c

LIBFT_DIR = libft/
GNL_DIR = gnl/
LISTS_DIR = lists/

GNL = $(GNL_DIR)get_next_line.a
LISTS = $(LISTS_DIR)lists.a
LIBFT = $(LIBFT_DIR)libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

GREEN = \033[0;32m
RESET = \033[0m

$(MINISHELL_NAME): $(MINISHELL_SRC) $(LIBFT) $(GNL) $(LISTS)
	$(CC) $(CFLAGS) $(MINISHELL_SRC) -L$(LIBFT_DIR) $(GNL) $(LISTS) -lft -o $(MINISHELL_NAME) $(LDFLAGS)
	@echo "$(GREEN) $(MINISHELL_NAME) successfully built.$(RESET)"

$(LIBFT):
	make -C $(LIBFT_DIR) --no-print-directory

$(GNL):
	make -C $(GNL_DIR) --no-print-directory

$(LISTS):
	make -C $(LISTS_DIR) --no-print-directory

all: $(MINISHELL_NAME)

clean:
	make -C $(LIBFT_DIR) --no-print-directory clean
	make -C $(GNL_DIR) --no-print-directory clean
	make -C $(LISTS_DIR) --no-print-directory clean
	rm -f $(MINISHELL_NAME)

fclean: clean
	make -C $(LIBFT_DIR) --no-print-directory fclean
	make -C $(LISTS_DIR) --no-print-directory clean
	make -C $(GNL_DIR) --no-print-directory fclean

re: fclean all
	@echo "$(GREEN)Rebuilding...$(RESET)"

phony: all clean fclean re
