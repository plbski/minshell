SOURCES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
          ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcpy.c ft_memmove.c ft_memset.c \
          ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strnstr.c \
          ft_strrchr.c ft_tolower.c ft_toupper.c ft_strncmp.c ft_memcmp.c ft_substr.c \
		  ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		  ft_num.c ft_printf.c utils.c

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
		ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJECTS = $(SOURCES:.c=.o)

ALL_OBJ = $(OBJECTS) $(BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

CC = gcc

NAME = libft.a

GREEN = \033[0;32m
RESET = \033[0m

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)
	@echo "$(GREEN)Libft build successfully.$(RESET)"

all: $(NAME)

bonus: $(ALL_OBJ)
	ar rcs $(NAME) $(ALL_OBJ)

clean:
	rm -f $(ALL_OBJ)
	@echo "$(GREEN)Libft .o cleaned.$(RESET)"

fclean: clean
	rm -f $(NAME)
	@echo "$(GREEN)Libft .a cleaned.$(RESET)"

re: fclean all

.SILENT: