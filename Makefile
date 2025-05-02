NAME := minishell
SRCS := src/main.c \
		src/garbage.c\
		
OBJS := $(SRCS:.c=.o)

CC := cc
CFLAGS := -Wall -Wextra -Werror -I /usr/local/opt/readline/include
LDFLAGS := -lreadline -L /usr/local/opt/readline/lib

HEADER_P := includes/parce.h
HEADER_m := includes/minishell.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c $(HEADER_P) $(HEADER_m)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)
NAME := minishell

SRCS := src/main.c
OBJS := $(SRCS:.c=.o)

CC := cc
CFLAGS := -Wall -Wextra -Werror -I /usr/local/opt/readline/include
LDFLAGS := -lreadline -L /usr/local/opt/readline/lib

HEADER := includes/minishell.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

re: fclean all

.SECONDARY: $(OBJS)

.PHONY: all clean fclean re
