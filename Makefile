# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/07 23:49:44 by kicausse          #+#    #+#              #
#    Updated: 2019/03/02 10:47:31 by modaouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= 	42sh

SRC 	=   srcs/main.c\
		    srcs/tools_1.c\
		    line_edition/set_terminal.c\
		    line_edition/line_edition.c\
		    line_edition/exit_le.c\
		    line_edition/tools_le.c

INC 	= 	libft/libft.h

CC		=	gcc

OBJ 	= 	$(SRC:.c=.o)

CFLAGS 	= 	-Wall -Wextra -Werror -Ilibft -Iincludes\
		  -g -fsanitize=address\
		  -fno-omit-frame-pointer\
		  -fsanitize-address-use-after-scope

all: $(NAME) libft/

$(NAME): libft/ includes/ Makefile $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME) -lncurses

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -o $@ -c $< 

re: fclean all

clean:
	make clean -C libft/
	/bin/rm -Rf $(OBJ)

fclean: clean
	make fclean -C libft/
	/bin/rm -Rf $(NAME)