NAME = lem-in

SRCS = ./src/main.c \
		./src/output.c \
		./src/parsing/parse_information.c \
		./src/path_finding/find_paths.c \

OBJS = $(SRCS:.c=.o)

INCLUDES = -I./libft \
			-I./ft_printf \
			-I./includes \
			-I./src \
			-I./src/parsing \

LINK = ./ft_printf/libftprintf.a \
		./libft/libft.a \

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: makeprintf makelibft $(NAME)

makelibft:
	@make -C libft all

makeprintf:
	@make -C ft_printf all

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(INCLUDES) $(LINK)

clean: clean_libft clean_ftprintf
	/bin/rm -f $(OBJS)

clean_libft:
	@make -C libft clean

clean_ftprintf:
	@make -C ft_printf clean

fclean: clean fclean_lem fclean_libft fclean_ftprintf

fclean_libft:
	@make -C libft fclean

fclean_lem:
	/bin/rm -f $(NAME)

re: fclean all

re_lem: fclean_lem all

fclean_ftprintf:
	@make -C ft_printf fclean
