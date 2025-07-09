NAME = minishell

CC = cc

CFLAGS =#-Wall -Wextra -Werror  # -g3  #-fsanitize=address

SRC = main.c utils00.c expand.c syntax_error.c lexer.c paring.c utils01.c \
	  execution/commend.c execution/execution.c  execution/pipe.c execution/signal.c\
	  execution/builtins/env.c  execution/builtins/echo.c \
	execution/builtins/export.c execution/builtins/unset.c execution/builtins/pwd.c\
	execution/builtins/cd.c  execution/readirections/red.c execution/readirections/her.c\
	garbage/ft_malloc.c  garbage/utils.c execution/builtins/exit.c\
	garbage/utils1.c

LIBFT = libft/libft.a

OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME):$(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -lreadline $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

clean:
	make -C libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)

re: fclean all