.SILENT:

SOURCES = ft_dprintf.c ft_num.c utils.c

OBJ = $(SOURCES:.c=.o)

CFLAGS = -Wall -Werror -Wextra

CC = gcc

NAME = printf.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)
	@echo "PRINTF generated"

all: $(NAME)

clean:
	rm -f $(OBJ)
	@if [ -z "$(QUIET)" ]; then echo "dprintf	cleaned"; fi

fclean: clean
	rm -f $(NAME)
	@echo "dprintf	successfully compiled"

re: fclean all