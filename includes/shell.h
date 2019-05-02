/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:26:51 by modaouch          #+#    #+#             */
/*   Updated: 2019/04/25 19:18:02 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <term.h>
# include <curses.h>
# include "../libft/libft.h"
# include "token_and_ast.h"

unsigned int     g_errorno;

typedef enum
{
						ER_DBACCES,
						ER_DBINFO,
						ER_SYNTAX
}						ERRORNO;

# define S_KEY_ARW_UP			65
# define S_KEY_ARW_DOWN			66
# define S_KEY_ARW_RIGHT		67
# define S_KEY_ARW_LEFT			68
# define S_KEY_ENTER			10
# define S_KEY_ERASE			127
// # define S_KEY_PRINTABLE		0
// # define S_KEY_SPACE			0
// # define S_KEY_ESC			27
// # define S_KEY_CTRL_D		4
// # define S_KEY_END			1
// # define S_KEY_NONE			0


# define MAX_KEY_LEN			15
# define BUFFER_LEN				255


typedef struct			s_edit
{
	struct termios	*termiold;
	struct termios	*termios;
	struct winsize	*wsize;
	char			*line;
	char			**env;
	int				i;
	int				autocompletion;	
	unsigned int	len;
	unsigned int	cursor_pos;
	unsigned int	len_max;
	unsigned int	prompt_size;
	char			tc_onoff;//for termcap like "dumb" , to have a usable shell
}						t_edit;

typedef struct			s_key_code
{
	unsigned char	*key;
	void			(*dump_key)(t_edit *line_e, char *buff);
}						t_key_code;

/*
** Initialization & Co
*/

void					set_terminal(t_edit *line_e);
void					toexit(t_edit *line_e, char *str);
struct termios*			term_backup(int bt);
struct termios*			term_raw(int bt);
void					init_line(t_edit *line_e);

/*
** Line edition
*/

int						line_edition(t_edit *line_e);
void					cursor_reposition(size_t n);
int						is_arrow(char *key);
int						ft_puti(int i);
void					ft_nlcr(void);
void					prompt_extend(void);

/*
** Line Lexing
*/

t_token*				get_next_token(char **line, int *i);
int						line_lexer(t_edit *line_e);
int						token_isword(int c);
int						token_is_io_nb(int c);
void					skip_predicat(char ** line, int *i, int (*pred)(int));
int						wordlen(char *line);

/*
** Parsing
*/

int						line_parser(t_ast **tree, t_edit *line_e);
void					complet_cmd(t_ast **tree, t_edit *line_e);
void					list_fct(t_ast **tree, t_edit *line_e);
void					list_prime_fct(t_ast **tree, t_edit *line_e);
void					list_dprime_fct(t_ast **tree, t_edit *line_e);
void					and_or_fct(t_ast **tree, t_edit *line_e);
void					and_or_prime_fct(t_ast **tree, t_edit *line_e);
void					and_or_op_fct(t_ast **tree, t_edit *line_e);
void					bang_fct(t_ast **tree, t_edit *line_e);
void					pipeline_fct(t_ast **tree, t_edit *line_e);
void					pipe_sequence_fct(t_ast **tree, t_edit *line_e);
void					pipe_sequence_prime_fct(t_ast **tree, t_edit *line_e);
void					command_fct(t_ast **tree, t_edit *line_e);
void					cmd_suffix_fct(t_ast **ast, t_edit *line_e);
void					cmd_suffix_opt_fct(t_ast **ast, t_edit *line_e);
void					cmd_suffix_prime_fct(t_ast **ast, t_edit *line_e);
void					cmd_suffix_dprime_fct(t_ast **ast, t_edit *line_e);
void					cmd_prefix_fct(t_ast **ast, t_edit *line_e);
void					cmd_prefix_prime_fct(t_ast **ast, t_edit *line_e);
void					io_redirect_fct(t_ast **ast, t_edit *line_e);
void					io_number_opt_fct(t_ast **ast, t_edit *line_e);
void					io_kind_fct(t_ast **ast, t_edit *line_e);
void					io_file(t_ast **ast, t_edit *line_e);
void					io_here(t_ast **ast, t_edit *line_e);
void					line_break_fct(t_ast **tree, t_edit *line_e);
void					separator_op_fct(t_ast **tree, t_edit *line_e);
void					newline_list_fct(t_ast **tree, t_edit *line_e);
void					newline_list_prime_fct(t_ast **tree, t_edit *line_e);
int						first_set(int kind, ...);//name tochange

/*
** Abstract Syntax Tree
*/

t_ast*					ast_new(t_token *tok);
void					ast_insert_left(t_token *tok, t_ast **root);
void					ast_insert_right(t_token *tok, t_ast **root);
void					infix_print_ast(t_ast *root);
void					rm_last_leaf(t_ast **root);
int						head_of_line(t_ast *ast);


/*
** Tools & Co
*/


#endif
