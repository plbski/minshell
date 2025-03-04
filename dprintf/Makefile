.SILENT:

SOURCES = ft_dprintf.c ft_num.c utils.c

OBJ = $(SOURCES:.c=.o)

CFLAGS = -Wall -Werror -Wextra

CC = gcc

NAME = printf.a

GREEN = \033[0;32m
CYAN =	\033[36m
RESET = \033[0m

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)
	@echo "dprintf $(GREEN)compiled$(RESET)"

all: $(NAME)

clean:
	rm -f $(OBJ)
	@if [ -z "$(QUIET)" ]; then echo "dprintf	$(CYAN)cleaned$(RESET)"; fi

fclean: clean
	rm -f $(NAME)
	@echo "dprintf	$(CYAN)force cleaned$(RESET)"

re: fclean all