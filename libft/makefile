# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/26 14:17:21 by monajjar          #+#    #+#              #
#    Updated: 2025/06/28 14:18:18 by monajjar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a

SRCS = ft_atoi.c \
       ft_isascii.c \
       ft_memcpy.c \
       ft_strlcat.c \
       ft_strrchr.c \
       ft_bzero.c \
       ft_isdigit.c \
       ft_memmove.c \
       ft_strlcpy.c \
       ft_tolower.c \
       ft_calloc.c \
       ft_isprint.c \
       ft_memset.c \
       ft_strlen.c \
       ft_toupper.c \
       ft_isalnum.c \
       ft_memchr.c \
       ft_strchr.c \
       ft_strncmp.c \
       ft_strcmp.c \
       ft_isalpha.c \
       ft_memcmp.c \
       ft_strdup.c \
       ft_strnstr.c \
	   ft_split.c \
	   ft_strjoin.c \
	   ft_substr.c \
	   ft_strtrim.c \
	   ft_itoa.c \
	   ft_striteri.c \
	   ft_strmapi.c \
	   ft_putchar_fd.c \
	   ft_putstr_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c \

SRCSB = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
              ft_lstiter_bonus.c \
              ft_lstmap_bonus.c \
		
OBJS := $(SRCS:.c=.o)

OBJSB := $(SRCSB:.c=.o)

CFLAGS := -Wall -Wextra -Werror

CC = cc


.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS)
	@ar -r $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS) $(OBJSB)

fclean: clean
	rm -rf $(NAME)

bonus: $(NAME) $(OBJSB)
	@ar -r $(NAME) $(OBJSB)

re: fclean all
.SECONDARY : $(OBJS) $(OBJSB)