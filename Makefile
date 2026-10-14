CC=cc
FLAG=-Wall -Wextra -Werror
SRC= main.c dining.c action.c manager.c start.c thread_tool.c time.c tools.c start_tool.c  threads_manager.c
OBJ=$(SRC:.c=.o)
NAME=philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAG) -o $@ $^

%.o: %.c philo.h
	$(CC) $(FLAG) -c $< -o $@

re: fclean all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
