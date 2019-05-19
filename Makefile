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

SRC =	Srcs/main.c\
		Srcs/init.c\
		Srcs/line_handling.c\
		Line_edition/set_terminal.c\
		Line_edition/line_edition.c\
		Line_edition/exit_le.c\
		Line_edition/tools_le.c\
		Line_edition/autocompletion.c\
		Line_edition/cursor_movement.c\
		Line_edition/file_list.c\
		Lexer/get_next_token.c\
		Lexer/token_tools.c\
		Lexer/token_isother.c\
		Lexer/token_redirect_great.c\
		Lexer/token_redirect_less.c\
		Lexer/token_word.c\
		Lexer/token_andor.c\
		Parser/ast_tools.c\
		Parser/parse_1_list.c\
		Parser/parse_2_and_or.c\
		Parser/parse_3_pipe_seq.c\
		Parser/parse_4_line_brk.c\
		Parser/parse_5_cmd.c\
		Parser/parse_6_cmd_prime.c\
		Parser/parse_7_io_fct.c\
		Parser/first_set.c\
		Inhibitor/inhibitors.c

OBJ = $(SRC:.c=.o)
#OBJ = $(patsubst %.c,%.o, $(SRC))

LIBFT = libft

LIB = libft/libft.a

INCLUDES = includes libft

DEPEN = $(INCLUDES) $(OBJ) Makefile libft/Makefile $(LIBFT)\
		Line_edition Srcs Parser Lexer Inhibitor

CC = gcc

CFLAGS +=  -Wall -Wextra -Werror -Ilibft\
			-g -fsanitize=address\
			-fno-omit-frame-pointer\
			-fsanitize-address-use-after-scope

all: $(NAME)

$(NAME): $(DEPEN)
	make -C $(LIBFT) all
	$(CC) $(CFLAGS) $(LIB) $(OBJ) libft/libft.a -o $(NAME) -lncurses

clean:
	make clean -C $(LIBFT)
	rm -f $(OBJ)

fclean:
	make fclean -C $(LIBFT)
	/bin/rm -f $(OBJ)
	/bin/rm -f ./$(NAME)

re: fclean all
