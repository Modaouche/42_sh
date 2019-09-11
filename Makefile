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
		srcs/main/init_term.c\
		srcs/main/init_tool.c\
		srcs/main/exit_handler.c\
		srcs/main/line_handling.c\
		srcs/line_edition/line_edition.c\
		srcs/line_edition/tools_le.c\
		srcs/line_edition/autocompletion.c\
		srcs/line_edition/autocompletion_building.c\
		srcs/line_edition/autocompletion_printing.c\
		srcs/line_edition/autocompletion_parser.c\
		srcs/line_edition/cursor_movement.c\
		srcs/line_edition/line_utils.c\
		srcs/line_edition/file_list.c\
		srcs/lexer/get_token.c\
		srcs/lexer/get_heredoc.c\
		srcs/lexer/token_tools.c\
		srcs/lexer/token_isother.c\
		srcs/lexer/token_redirect_great.c\
		srcs/lexer/token_redirect_less.c\
		srcs/lexer/token_word.c\
		srcs/lexer/token_andor.c\
		srcs/parser/1_parse_list.c\
		srcs/parser/2_parse_and_or.c\
		srcs/parser/3_parse_pipe_seq.c\
		srcs/parser/4_parse_line_brk.c\
		srcs/parser/5_parse_cmd.c\
		srcs/parser/6_parse_cmd_prime.c\
		srcs/parser/7_parse_io_fct.c\
		srcs/parser/ast_tools.c\
		srcs/parser/ast_head_and_cmp.c\
		srcs/signals/signal_handler.c\
		srcs/exec/exec.c\
		srcs/exec/exec_and_or.c\
		srcs/exec/exec_cmd.c\
		srcs/exec/exec_cmp.c\
		srcs/exec/exec_tools.c\
		srcs/exec/exec_builtin.c\
		srcs/jobs/foreground_and_background.c\
		srcs/jobs/job_utils.c\
		srcs/jobs/job_tools.c\
		srcs/jobs/launch_job.c\
		srcs/jobs/stop_and_done_job.c\
		srcs/inhibitor/inhibitors.c\
		srcs/inhibitor/quote_handling.c\
		srcs/inhibitor/word_handling.c\
		srcs/inhibitor/expanded_word.c

OBJ = $(SRC:.c=.o)

LIBFT = srcs/libft

LIB = $(LIBFT)/libft.a

HEADERS = includes/shell.h includes/token_and_ast.h\
		includes/signal_handler.h includes/error_handler.h\
		includes/job.h



INCLUDES = -Iincludes -I$(LIBFT)

DEPEN = $(OBJ) Makefile $(HEADERS)

CC = gcc

CFLAGS +=  -Wall -Wextra -Werror $(INCLUDES)
	#		-g3 -fsanitize=address\
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
