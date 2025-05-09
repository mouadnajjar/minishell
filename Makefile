NAME := minishell


SRC_DIR := src
INC_DIR := includes
LIBFT_DIR := libft


SRCS := $(SRC_DIR)/main.c \
        $(SRC_DIR)/parsing/garbage.c \
        $(SRC_DIR)/parsing/parse_input.c \
        $(SRC_DIR)/parsing/tokenize.c \
		$(SRC_DIR)/parsing/parse_help.c

OBJS := $(SRCS:.c=.o)
HEADER := $(INC_DIR)/minishell.h

CC := cc
INCLUDES := -I$(INC_DIR) -I$(LIBFT_DIR) -I/usr/local/opt/readline/include
CFLAGS := -Wall -Wextra -Werror -g $(INCLUDES)
LDFLAGS := -lreadline -L/usr/local/opt/readline/lib
LIBFT_A := $(LIBFT_DIR)/libft.a


all: $(LIBFT_A) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) $(LIBFT_A)

%.o: %.c $(HEADER_P) $(HEADER_m)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR) bonus

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
