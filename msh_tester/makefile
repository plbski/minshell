TESTER_SRC = tester.c
MINI_SRC = mini.c

TESTER_NAME = tester
MINI_NAME = mini

CC = cc
CFLAGS = -Wall -Werror -Wextra

CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

LIBFT_DIR = ../libft/
$(LIBFT):
	make -C $(LIBFT_DIR) --no-print-directory

$(TESTER_NAME): $(TESTER_SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(TESTER_SRC) -L$(LIBFT_DIR) $(GNL) $(DPRINTF) -o $(TESTER_NAME)

$(MINI_NAME): $(MINI_SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(MINI_SRC) -L$(LIBFT_DIR) $(GNL) $(DPRINTF) -lft -o $(MINI_NAME) $(LDFLAGS)


all: $(TESTER_NAME) $(MINI_NAME)

clean:
	rm -f $(TESTER_NAME)
	rm -f $(MINI_NAME)

fclean: clean

re: fclean all

phony: all clean fclean re

phony: all clean fclean re
