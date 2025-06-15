# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 10:12:25 by monajjar          #+#    #+#              #
#    Updated: 2024/11/12 17:48:22 by monajjar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libftprintf.a

SRCS = ft_printf.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_putint.c \
		ft_printunsigned.c \
		ft_hexaprint.c \
		ft_printptr.c \
	
OBJS := $(SRCS:.c=.o)

OBJSB := $(SRCSB:.c=.o)

CFLAGS := -Wall -Wextra -Werror

CC = cc

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS)
	ar -rsc $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)



re: fclean all
.SECONDARY : $(OBJS)