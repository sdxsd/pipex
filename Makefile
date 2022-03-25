##
# PIPEX
#

# Variables:
CC = clang
CFLAGS = -g -Wall -Wextra -Werror
LIB = libft/libft.a
NAME = pipex
CFILES = \
			src/pipex.c

all: $(NAME)

$(NAME): $(LIB)
	$(CC) $(CFLAGS) $(CFILES) $(LIB) -o $(NAME)

$(LIB):
	make -C libft/

clean:
	@rm -f $(NAME)

fclean: clean

re: fclean $(NAME)

.PHONY: all clean fclean re

# end
