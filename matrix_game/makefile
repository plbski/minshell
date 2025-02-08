SRC = \
c_files/init.c c_files/render.c c_files/update_loop.c c_files/input.c c_files/utils.c \
c_files/update_entities.c c_files/proj.c c_files/update_proj.c

NAME=matrix

CC = gcc
CFLAGS = -Wall -Werror -Wextra

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

all: $(NAME)

debug: $(SRC)
	$(CC) $(CFLAGS) -fsanitize=address -g $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all

.PHONY: all clean re debug