NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = philo.c utils.c init.c monitor.c routine.c threads.c single_philo.c
OBJ = $(SRC:.c=.o)

all: print_name $(NAME)

print_name:
	@echo "\033[1;32mmmakhlou Project\033[0m"

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
