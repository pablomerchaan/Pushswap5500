# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paperez- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 12:55:03 by paperez-          #+#    #+#              #
#    Updated: 2024/12/11 13:30:11 by paperez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

SOURCES = ft_printf.c ft_putchar.c ft_putstr.c \
		  ft_putpointer.c ft_puthexa.c ft_putnbr.c \
		  ft_putuint.c ft_aux.c pushswap.c transform.c \
		  transform_r.c transform_rr.c transform_s.c \
		  transformrot.c emitrot.c utils.c sortthree.c \
		 sorted.c lookahead.c checks.c ft_split.c 

OBJECTS = $(SOURCES:.c=.o)

CC = gcc

CFLAGS = -Wextra -Wall -Werror

INLCUDES = -I ./

all: $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $(NAME)

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
