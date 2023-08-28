# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 20:33:20 by jrosmari          #+#    #+#              #
#    Updated: 2023/02/04 15:09:47 by jrosmari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftprintf.a

SRCS=ft_printf.c ft_printchars.c ft_printnbrs.c ft_printhexes.c

OBJECTS=ft_printf.o ft_printchars.o ft_printnbrs.o ft_printhexes.o

INCLUDES=./

all: $(NAME)

$(NAME): $(SRCS) ft_printf.h
	cc -Wall -Wextra -Werror -I$(INCLUDES) -c $(SRCS)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)


clean:
	/bin/rm -f $(OBJECTS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re






