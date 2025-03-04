SOURCES 	= get_next_line.c get_next_line_utils.c

OBJ			= $(SOURCES:.c=.o)

OBJ_BONUS	= $(BONUS:.c=.o)

NAME 		= get_next_line.a

CFLAGS 		= -Wall -Werror -Wextra -D BUFFER_SIZE=$(BUFFER_SIZE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

GREEN		= \033[0;32m
CYAN		= \033[36m
RESET		= \033[0m

BUFFER_SIZE	?= 30

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
	@echo "GNL	$(GREEN)compiled$(RESET)"

test:
	cc -fsanitize=address -g *.c -D BUFFER_SIZE=$(BUFFER_SIZE)

clean:
	rm -f $(OBJ)
	@if [ -z "$(QUIET)" ]; then echo "GNL	$(CYAN)cleaned$(RESET)"; fi

fclean: clean
	rm -f $(NAME)
	@echo "GNL	$(CYAN)force cleaned$(RESET)"

all: $(NAME)

re: fclean all
