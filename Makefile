# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/20 17:03:40 by modaouch          #+#    #+#              #
#    Updated: 2019/04/25 20:18:39 by modaouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

SRC =	srcs/main.c\
		srcs/tools_1.c\
		line_edition/set_terminal.c\
		line_edition/line_edition.c\
		line_edition/exit_le.c\
		line_edition/tools_le.c\
		Parser/get_next_token.c\
		Parser/line_parser.c\
		Parser/token_tools.c\
		Parser/ast_tools.c\
		Parser/parse_1_list.c\
		Parser/parse_2_and_or.c\
		Parser/parse_3_pipe_seq.c\
		Parser/parse_4_line_brk.c\
		Parser/parse_5_cmd.c\
		Parser/parse_6_cmd_prime.c\
		Parser/parse_7_io_fct.c\
		Parser/first_set.c

OBJ = $(SRC:.c=.o)
#OBJ = $(patsubst %.c,%.o, $(SRC))

LIBFT = libft

LIB = libft/libft.a

INCLUDES = includes libft

DEPEN = $(INCLUDES) $(OBJ) Makefile libft/Makefile $(LIBFT)\
		srcs\
		line_edition

CC = gcc

CFLAGS += -Wall -Wextra -Werror -Ilibft \
		  -g -fsanitize=address\
		  -fno-omit-frame-pointer\
		  -fsanitize-address-use-after-scope

all: $(NAME)


$(NAME): $(DEPEN)
	make -C $(LIBFT) all
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME) -lncurses

clean:
	make clean -C $(LIBFT)
	rm -f $(OBJ)

fclean:
	make fclean -C $(LIBFT)
	/bin/rm -f $(OBJ)
	/bin/rm -f ./$(NAME)

re: fclean all
