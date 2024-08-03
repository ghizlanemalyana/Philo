flags = -Wall -Wextra -Werror
sources = init.c main.c parse.c routine.c threads.c utils.c
objs = $(sources:.c=.o)
NAME = philo

all: $(NAME)

$(NAME): $(objs)
	cc $(flags) $(objs) -o $(NAME)

%.o : %.c philo.h
	cc $(flags) -c $< -o $@

clean:
	rm -f $(objs)

fclean: clean
	rm -f $(NAME)

re: fclean all
