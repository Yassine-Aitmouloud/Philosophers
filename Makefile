NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

PHILO_SRC = philo.c 

PHILO_OBJ = $(PHILO_SRC:.c=.o)

all: $(NAME)

$(NAME):	$(PHILO_OBJ)
	$(CC)	$(CFLAGS)	$^ -o	$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(PHILO_OBJ)

fclean: clean
	rm -rf $(NAME)

.PHONY: all clean fclean re

re: fclean all

.SECONDARY: $(PHILO_OBJ)