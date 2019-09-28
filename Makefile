# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/20 17:03:40 by modaouch          #+#    #+#              #
#    Updated: 2019/09/23 12:20:02 by araout           ###   ########.fr        #
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
		srcs/line_edition/tools_le2.c\
		srcs/line_edition/autocompletion.c\
		srcs/line_edition/autocompletion_building.c\
		srcs/line_edition/autocompletion_printing.c\
		srcs/line_edition/print_comp_list.c\
		srcs/line_edition/autocompletion_parser.c\
		srcs/line_edition/cursor_movement.c\
		srcs/line_edition/cursor_movement_advanced.c\
		srcs/line_edition/parse_word.c\
		srcs/line_edition/line_utils.c\
		srcs/line_edition/line_insertion.c\
		srcs/line_edition/file_list.c\
		srcs/line_edition/list_merge.c\
		srcs/line_edition/build_list.c\
		srcs/line_edition/autocompletion_searching.c\
		srcs/line_edition/get_autocomp_word.c\
		srcs/line_edition/escape_autocomp.c\
		srcs/line_edition/word_movement.c\
		srcs/line_edition/line_movement.c\
		srcs/line_edition/key_handler.c\
		srcs/line_edition/arrows_handler.c\
		srcs/line_edition/hist_movement.c\
		srcs/line_edition/autocomp_manage.c\
		srcs/lexer/get_token.c\
		srcs/lexer/get_heredoc.c\
		srcs/lexer/token_tools.c\
		srcs/lexer/token_isother.c\
		srcs/lexer/token_redirect_great.c\
		srcs/lexer/token_redirect_less.c\
		srcs/lexer/token_word.c\
		srcs/lexer/token_andor.c\
		srcs/parser/parse_list.c\
		srcs/parser/parse_and_or.c\
		srcs/parser/parse_pipe_seq.c\
		srcs/parser/parse_line_brk.c\
		srcs/parser/parse_cmd.c\
		srcs/parser/parse_cmd_prime.c\
		srcs/parser/parse_cmd_suffix_prime_fct.c\
		srcs/parser/parse_cmd_suffix_dprime_fct.c\
		srcs/parser/parse_cmd_prefix_fct.c\
		srcs/parser/parse_io_fct.c\
		srcs/parser/parse_io_file.c\
		srcs/parser/parse_io_here.c\
		srcs/parser/ast_tools.c\
		srcs/parser/ast_tools_2.c\
		srcs/parser/ast_head_and_cmp.c\
		srcs/signals/signal_handler.c\
		srcs/exec/exec.c\
		srcs/exec/exec_and_or.c\
		srcs/exec/exec_verif.c\
		srcs/exec/exec_cmp.c\
		srcs/exec/exec_tools.c\
		srcs/exec/exec_cmd_and_bu.c\
		srcs/jobs/foreground_and_background.c\
		srcs/jobs/job_utils.c\
		srcs/jobs/job_tools.c\
		srcs/jobs/launch_job.c\
		srcs/jobs/stop_and_done_job.c\
		srcs/inhibitor/inhibitors.c\
		srcs/inhibitor/quote_handling.c\
		srcs/inhibitor/word_handling.c\
		srcs/inhibitor/expanded_word.c\
		srcs/inhibitor/ft_dollar_cmd.c\
		srcs/options/options.c\
		srcs/history/history.c\
		srcs/history/history_utils.c\
		srcs/history/ft_fc.c\
		srcs/history/ft_fc_print.c\
		srcs/history/ft_fc_utils.c\
		srcs/history/ft_fc_error.c\
		srcs/history/ft_build_history.c\
		srcs/history/ft_fc_s.c\
		srcs/history/ft_fc_editor.c\
		srcs/env/misc_env.c\
		srcs/env/init_env.c\
		srcs/env/ft_cd.c\
		srcs/env/ft_errors.c\
		srcs/env/built_in_init.c\
		srcs/env/built_in_function.c\
		srcs/env/setenv.c\
		srcs/env/setenv_equal.c\
		srcs/builtin/echo/main_echo.c\
		srcs/builtin/type/type.c\
		srcs/builtin/alias/alias.c\
		srcs/builtin/alias/alias_utils.c\
		srcs/alias/alias.c\
		srcs/builtin/test/test.c\
		srcs/builtin/test/ft_file_type.c\
		srcs/builtin/test/ft_file_type_bis.c\
		srcs/builtin/test/ft_chmod_file.c\
		srcs/builtin/test/ft_chmod_file_bis.c\
		srcs/builtin/test/test_flag_file.c\
		srcs/builtin/test/test_flag_str.c\
		srcs/builtin/test/test_flag_nbr.c\
		srcs/builtin/test/test_flag_tools.c\
		srcs/builtin/test/tools.c\
		srcs/builtin/test/tools_2.c\
		srcs/builtin/jobs/jobs.c\
		srcs/builtin/jobs/ft_fg_bg.c\
		srcs/param_expansion/main.c\
		srcs/param_expansion/param.c\
		srcs/param_expansion/parambis.c\
		srcs/param_expansion/parsing.c\
		srcs/param_expansion/tools.c\
		srcs/param_expansion/ft_joinarg.c \
		srcs/param_expansion/param_assign.c\
		srcs/tild/tild.c \
		srcs/utils/utils.c

OBJ = $(SRC:.c=.o)

LIBFT = srcs/libft

LIB = $(LIBFT)/libft.a

HEADERS = includes/shell.h includes/token_and_ast.h includes/signal_handler.h \
		includes/history.h includes/env.h includes/built_in.h includes/ft_test.h \
	    includes/error_handler.h includes/job.h includes/param_expansion.h \
	    includes/tild.h



INCLUDES = -Iincludes -I$(LIBFT)

DEPEN = $(OBJ) Makefile $(HEADERS)

CC = gcc

CFLAGS +=  -Wall -Wextra -Werror $(INCLUDES)#\
			-g3 -fsanitize=address\
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
