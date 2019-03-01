# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: modaouch <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/20 17:03:40 by modaouch          #+#    #+#              #
#    Updated: 2018/06/23 21:27:30 by modaouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = src/ft_conv1.c\
	  src/ft_conv2.c\
	  src/ft_conv3.c\
	  src/ft_prec1.c\
	  src/ft_printf.c\
	  src/libft/ft_itoa.c\
	  src/libft/ft_strdel.c\
	  src/libft/ft_itoa_base.c\
	  src/libft/ft_putchar.c\
	  src/libft/ft_putstr.c\
	  src/libft/ft_strlen.c\
	  src/libft/ft_isdigit.c\
	  src/libft/ft_strncmp.c\
	  src/libft/ft_strnew.c\
	  src/libft/ft_tolower.c\
	  src/libft/ft_toupper.c\
	  src/libft/ft_bzero.c

INCLUDES = includes/ft_conv.h\
		   includes/ft_printf.h\
		   src/libft/libft.h

LIBFT = src/libft

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME) $(LIBFT)

$(NAME): $(OBJ) Makefile $(INCLUDES)
	ar rc $@ $(OBJ)
	ranlib $@

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ)
	rm -f ./$(NAME)

re: fclean all
	#gcc -c $(CFLAGS) $(SRC)
	#ar rc $(NAME) $(OBJ)
	#ranlib $(NAME)
