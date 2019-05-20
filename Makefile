# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/20 17:03:40 by modaouch          #+#    #+#              #
#    Updated: 2019/05/11 18:44:34 by modaouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

SRC =	srcs/main/main.c\
		srcs/main/init.c\
		srcs/main/line_handling.c\
		srcs/line_edition/set_terminal.c\
		srcs/line_edition/line_edition.c\
		srcs/line_edition/exit_le.c\
		srcs/line_edition/tools_le.c\
		srcs/line_edition/autocompletion.c\
		srcs/line_edition/autocompletion_printing.c\
		srcs/line_edition/cursor_movement.c\
		srcs/line_edition/file_list.c\
		srcs/lexer/get_next_token.c\
		srcs/lexer/token_tools.c\
		srcs/lexer/token_isother.c\
		srcs/lexer/token_redirect_great.c\
		srcs/lexer/token_redirect_less.c\
		srcs/lexer/token_word.c\
		srcs/lexer/token_andor.c\
		srcs/parser/ast_tools.c\
		srcs/parser/parse_1_list.c\
		srcs/parser/parse_2_and_or.c\
		srcs/parser/parse_3_pipe_seq.c\
		srcs/parser/parse_4_line_brk.c\
		srcs/parser/parse_5_cmd.c\
		srcs/parser/parse_6_cmd_prime.c\
		srcs/parser/parse_7_io_fct.c\
		srcs/parser/first_set.c\
		srcs/inhibitor/inhibitors.c

OBJ = $(SRC:.c=.o)

LIBFT = srcs/libft

LIB = $(LIBFT)/libft.a

HEADERS = includes/shell.h includes/token_and_ast.h

INCLUDES = -Iincludes -I$(LIBFT)

DEPEN = $(OBJ) Makefile $(HEADERS)

CC = gcc

CFLAGS +=  -Wall -Wextra -Werror $(INCLUDES)\
	#		-g -fsanitize=address\
			-fno-omit-frame-pointer\
			-fsanitize-address-use-after-scope

all: lib $(NAME)

$(NAME): $(DEPEN)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME) -lncurses
lib:
	make -C $(LIBFT) all

clean:
	make clean -C $(LIBFT)
	rm -f $(OBJ)

fclean:
	make fclean -C $(LIBFT)
	/bin/rm -f $(OBJ)
	/bin/rm -f ./$(NAME)

re: fclean all
