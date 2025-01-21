SOURCES = get_next_line.c

OBJ = $(SOURCES:.c=.o)

OBJ_BONUS = $(BONUS:.c=.o)

NAME = get_next_line.a

CFLAGS = -Wall -Werror -Wextra -D BUFFER_SIZE=$(BUFFER_SIZE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

GREEN = \033[0;32m
RESET = \033[0m

BUFFER_SIZE ?= 30

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
	@echo "$(GREEN)GNL lib successfully compiled.$(RESET)"

test:
	cc -fsanitize=address -g *.c -D BUFFER_SIZE=$(BUFFER_SIZE)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

all: $(NAME)

re: fclean all
