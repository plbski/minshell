SRC_DIR_CLIST = c_files/clst
SRC_DIR_DBLIST = c_files/dblst

UTILS_SRC = c_files/utils.c
CLST_SRC = $(SRC_DIR_CLIST)/check.c $(SRC_DIR_CLIST)/delete.c $(SRC_DIR_CLIST)/init.c $(SRC_DIR_CLIST)/use.c
DBLST_SRC = $(SRC_DIR_DBLIST)/check.c $(SRC_DIR_DBLIST)/delete.c $(SRC_DIR_DBLIST)/init.c $(SRC_DIR_DBLIST)/use.c

SOURCES = $(CLST_SRC) $(DBLST_SRC) $(UTILS_SRC)

OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -Wall -Wextra -Werror

CC = gcc

GREEN = \033[0;32m
CYAN =	\033[36m
RESET = \033[0m

NAME = lists.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)
	@echo "Lists	$(GREEN)compiled$(RESET)"

all: $(NAME)

clean:
	rm -f $(OBJECTS)
	@if [ -z "$(QUIET)" ]; then echo "Lists	$(CYAN)cleaned$(RESET)"; fi

fclean: clean
	rm -f $(NAME)
	@echo "Lists	$(CYAN)force cleaned$(RESET)"

re: fclean all

.SILENT: