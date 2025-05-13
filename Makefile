NAME := minishell


SRC_DIR := src
INC_DIR := includes
LIBFT_DIR := libft

EXEC = $(SRC_DIR)/main.c \
	   $(SRC_DIR)/execution/env.c \
	   $(SRC_DIR)/execution/path_utils.c \
	   $(SRC_DIR)/execution/memory_free.c \
	   $(SRC_DIR)/execution/executor.c \
	   $(SRC_DIR)/execution/redirection.c \
	   $(SRC_DIR)/execution/helper_execution.c \
	   $(SRC_DIR)/execution/builtins/builtin_echo.c \
	   $(SRC_DIR)/execution/builtins/built_in_utils.c \
	   $(SRC_DIR)/execution/builtins/built_ins.c \
	   $(SRC_DIR)/execution/builtins/builtin_pwd.c \
	   $(SRC_DIR)/execution/builtins/builtin_cd.c \

SRCS :=  $(EXEC) \

OBJS := $(SRCS:.c=.o)
HEADER := $(INC_DIR)/minishell.h

CC := cc
INCLUDES := -I$(INC_DIR) -I$(LIBFT_DIR) -I/usr/local/opt/readline/include
CFLAGS := -Wall -Wextra -Werror $(INCLUDES)
LDFLAGS := -lreadline -L/usr/local/opt/readline/lib
LIBFT_A := $(LIBFT_DIR)/libft.a


all: $(LIBFT_A) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) $(LIBFT_A)

%.o: %.c $(HEADER)
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
