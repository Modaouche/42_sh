/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:26:51 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 11:58:02 by modaouch         ###   ########.fr       */
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
	struct termios		*termiold;
	struct termios		*termios;
	struct winsize		*wsize;
	char			*line;
	char			**env;
	t_list			*autocompletion_list;
	int			autocompletion;	
	unsigned int		autocompletion_idx;
	unsigned int		autocompletion_size;
	unsigned int 		autocompletion_maxcol;
	unsigned int		len;
	unsigned int					ofst;
	unsigned int		cursor_pos;
	unsigned int		len_max;
	unsigned int		prompt_size;
	char				tc_onoff;//for termcap like "dumb" , to have a usable shell
}						t_edit;

typedef struct			s_key_code
{
	unsigned char		*key;
	void				(*dump_key)(t_edit *line_e, char *buff);
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
size_t					print_prompt(unsigned int btn);
void					cursor_start(t_edit *line_e);
void					cursor_end(t_edit *line_e);
void					cursor_actualpos(t_edit *line_e);
void					cursor_after(t_edit *line_e);

/*
**  Line edition - Autocompletion
*/


t_list					*build_completion_list(char *str, int len, char **env,
						unsigned int *list_size);
void					print_autocompletion_list(t_edit *line_e, int highlight);
int     				get_last_common_char(t_list *list);


/*
** Line Lexing
*/

t_token*				get_next_token(const char **line, unsigned int *i);
int						line_lexer(t_edit *line_e);
void					skip_predicat(const char ** line, unsigned int *i, int (*pred)(int));
int						wordlen(char *line);
int						ft_isspace_tok(int c);
void					fill_token_tab(void);
void    				token_isword(t_token *actual_token, const char *line, unsigned int *i);
void    				token_isio_nb(t_token *actual_token, const char *line, unsigned int *i);
void    				token_iseof(t_token *actual_token, const char *line, unsigned int *i);
void    				token_isnewl(t_token *actual_token, const char *line, unsigned int *i);
void    				token_isbang(t_token *actual_token, const char *line, unsigned int *i);
void    				token_issemi(t_token *actual_token, const char *line, unsigned int *i);
void    				token_isamper(t_token *actual_token, const char *line, unsigned int *i);
void    				token_isand(t_token *actual_token, unsigned int *i);
void    				token_ispipe(t_token *actual_token, const char *line, unsigned int *i);
void    				token_isor(t_token *actual_token, unsigned int *i);
void    				token_isgreat(t_token *actual_token, const char *line, unsigned int *i);
void    				token_isdgreat(t_token *actual_token, unsigned int *i);
void    				token_isclobber(t_token *actual_token,  unsigned int *i);
void    				token_isgreatand(t_token *actual_token, unsigned int *i);
void    				token_isless(t_token *actual_token, const char *line, unsigned int *i);
void    				token_isdless(t_token *actual_token, const char *line, unsigned int *i);
void    				token_isdlessdash(t_token *actual_token, unsigned int *i);
void    				token_islessgreat(t_token *actual_token, unsigned int *i);
void    				token_islessand(t_token *actual_token, unsigned int *i);

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
** Inhibitor
*/

int    					*ext_quotes(const char *line, char *word);
int  					ft_isword(int c);
char 					*get_word(const char *line);


/*
** Tools & Co
*/


#endif
