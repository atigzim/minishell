# Compiler and flags
CC = cc
CFLAGS = #-Wall -Wextra -Werror
LDFLAGS = -lreadline  # Readline and ncurses dependencies

# Project name
NAME = minishell

# Source files
SRCS = main.c  minishell.c syntax_errors.c Tokenization/split_store.c \
	libft_functions/utils.c libft_functions/split_cmd.c libft_functions/lst_utils.c \
	libft_functions/ft_split.c parsing/check_type_cmd.c \
	libft_functions/ft_strjoin.c parsing/builtins.c expand/expand.c libft_functions/utils1.c \
	expand/expand_01.c\
	execution/builtins/env.c execution/execution.c execution/builtins/echo.c \
	execution/builtins/export.c

# Object files
OBJS = $(SRCS:.c=.o)

# Header files (if any)
HEADERS = minishell.h

# Default target
all: $(NAME)

# Build executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

# Compile .c to .o
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

# Full clean (objects and executable)
fclean: clean
	rm -f $(NAME)

# Rebuild project
re: fclean all

# Phony targets (targets that aren't files)
.PHONY: all clean fclean re