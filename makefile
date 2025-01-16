.SILENT:

MINISHELL_SRC = c_files/minishell.c c_files/prompt.c c_files/utils.c c_files/init.c c_files/cd.c c_files/pwd.c
LIBFT_SRC = libft/
MINISHELL_NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT = $(LIBFT_SRC)libft.a
LDFLAGS = -lreadline

GREEN = \033[0;32m
RESET = \033[0m

$(MINISHELL_NAME): $(MINISHELL_SRC) $(LIBFT)
	@echo "$(GREEN)Compiling $(MINISHELL_NAME)$(RESET)"
	$(CC) $(CFLAGS) $(MINISHELL_SRC) -L$(LIBFT_SRC) -lft -o $(MINISHELL_NAME) $(LDFLAGS)

$(LIBFT):
	@echo "$(GREEN)Compiling libft...$(RESET)"
	make -C $(LIBFT_SRC) --no-print-directory

all: $(MINISHELL_NAME)

clean:
	@echo "$(GREEN)Cleaning...$(RESET)"
	make -C $(LIBFT_SRC) --no-print-directory clean
	rm -f $(MINISHELL_NAME)

fclean: clean
	@echo "$(GREEN)Full Cleaning...$(RESET)"
	make -C $(LIBFT_SRC) --no-print-directory fclean

re: fclean all
	@echo "$(GREEN)Rebuilding...$(RESET)"

phony: all clean fclean re
