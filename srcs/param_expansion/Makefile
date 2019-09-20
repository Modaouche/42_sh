# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/04 00:44:45 by mgheraie          #+#    #+#              #
#    Updated: 2019/09/20 23:32:32 by mgheraie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= 	param_expansion

SRC 	= 	srcs/main.c\
			srcs/parsing.c\
			srcs/param.c\
			srcs/parambis.c\
			srcs/tools.c\

INC 	= 	includes/ft_tild.h

CC		=	gcc

OBJ 	= 	$(SRC:.c=.o)

CFLAGS 	= 	-g3 -fsanitize=address -Wall -Wextra -Werror -Ilibft -Iincludes
#CFLAGS 	= 	-g3 -Wall -Wextra -Werror -Ilibft -Iincludes


all: $(NAME) libft/

$(NAME): libft/ includes/ Makefile $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -o $@ -c $< 

re: fclean all

clean:
	make clean -C libft/
	/bin/rm -Rf $(OBJ)

fclean: clean
	make fclean -C libft/
	/bin/rm -Rf $(NAME)
