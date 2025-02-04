.SILENT:

GEN_SRC = gen.c 
CHOOSE_SRC = choose_exit.c
REV_SRC = rev.c
SORT_SRC = sort.c

GEN_NAME = gen
CHOOSE_NAME = choose
REV_NAME = rev
SORT_NAME = sort

CC = gcc
CFLAGS = -Wall -Wextra -Werror

GREEN = 	\033[0;32m
RESET = 	\033[0m

$(GEN_NAME):
	$(CC) $(CFLAGS) $(GEN_SRC) -o $(GEN_NAME)

$(CHOOSE_NAME):
	$(CC) $(CFLAGS) $(CHOOSE_SRC) -o $(CHOOSE_NAME)

$(REV_NAME):
	$(CC) $(CFLAGS) $(REV_SRC) -o $(REV_NAME)

$(SORT_NAME):
	$(CC) $(CFLAGS) $(SORT_SRC) -o $(SORT_NAME)

all: $(GEN_NAME) $(CHOOSE_NAME) $(REV_NAME) $(SORT_NAME)
	@echo "$(GREEN)tst_prgs$(RESET)	suffessfully compiled."

$(NAME): all

clean:
	rm -f $(GEN_NAME) $(CHOOSE_NAME) $(REV_NAME) $(SORT_NAME)

re: clean all