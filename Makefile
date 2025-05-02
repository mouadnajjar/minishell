# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/02 09:27:27 by monajjar          #+#    #+#              #
#    Updated: 2025/05/02 09:36:43 by monajjar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= minishell

SRCS:= src/main.c \

OBJS:= $(SRCS:.c=.o)

CC:= cc

CFLAGS:= -Wall -Wextra -Werror

HEADER:= includes/minishell.h

all: $(NAME)

$(NAME): $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
fclean : clean
	rm -rf $(NAME)
re: fclean all

.SECONDARY: $(OBJS)

.PHONY: all clean fclean re
