##
# PIPEX
#

# Variables:
CC = clang
CFLAGS = -g -Wall -Wextra -Werror
NAME = pipex
CFILES = \
			src/pipex.c

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(CFILES) -o $(NAME)

clean:
	@rm -f $(NAME)

fclean: clean

re: fclean $(NAME)

.PHONY: all clean fclean re

# end
