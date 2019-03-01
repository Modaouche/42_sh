# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/20 17:03:40 by modaouch          #+#    #+#              #
#    Updated: 2019/02/07 13:42:39 by modaouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

SRC =	srcs/main.c\
		srcs/tools_1.c\
		line_edition/set_terminal.c\
		line_edition/line_edition.c\
		line_edition/exit_le.c\
		line_edition/tools_le.c

LIB = libft/libft.a\
	  libft/ft_printf/libftprintf.a\

OBJ = $(SRC:.c=.o)
#OBJ = $(patsubst %.c,%.o, $(SRC))

INCLUDES = libft/ft_printf/includes/ft_conv.h\
		   libft/ft_printf/includes/ft_printf.h\
		   libft/libft.h\
		   includes/shell.h\
		   includes/key_fct_p.h

LIBFT = libft

LIBFTPRINTF = libft/ft_printf/

DIRPRINTF = libft/ft_printf/src\
		    libft/ft_printf/includes\
		    libft/ft_printf/src/libft

DEPEN = $(INCLUDES) $(SRC) $(OBJ) Makefile libft/Makefile\
		libft/ft_printf/Makefile $(LIBFT) $(LIBFTPRINTF) srcs line_edition

CC = gcc

CFLAGS +=  -Wall -Wextra -Werror\
		  -g -fsanitize=address\
		  -fno-omit-frame-pointer\
		  -fsanitize-address-use-after-scope

all: $(NAME)


$(NAME): $(DEPEN)
	make -C $(LIBFT) all
	make -C $(LIBFTPRINTF) all
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME) -lncurses

clean:
	make clean -C $(LIBFT)
	make clean -C $(LIBFTPRINTF)
	rm -f $(OBJ)

fclean:
	make fclean -C $(LIBFT)
	make fclean -C $(LIBFTPRINTF)
	/bin/rm -f $(OBJ)
	/bin/rm -f ./$(NAME)

re: fclean all
