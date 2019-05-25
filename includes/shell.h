/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:26:51 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 12:34:07 by modaouch         ###   ########.fr       */
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
						NO_ERROR,
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
# define TOKEN_CMP				";\n&|!<>"
# define BKSH_DQT_CMP				"\\$\""

typedef struct 			s_file
{
	char			*name;
	size_t			len;
	int				type;
	struct s_file	*next;
}						t_file;

typedef struct			s_edit
{
	struct termios		*termiold;
	struct termios		*termios;
	struct winsize		*wsize;
	char				*line;
	char				**env;
	t_file				*autocomp_list;
	int					autocomp;	
	unsigned int		autocomp_idx;
	unsigned int		autocomp_size;
	unsigned int		autocomp_point;
	unsigned int 		autocomp_maxcol;
	unsigned int 		autocomp_maxrow;
	unsigned int		autocomp_quote;
	unsigned int		len;
	unsigned int		ofst;
	unsigned int		cursor_pos;
	unsigned int		len_max;
	unsigned int		prompt_size;
	unsigned int		winsize_col;
	unsigned int		winsize_row;
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
void					toexit(t_edit *line_e, char *str, int err);
struct termios*			term_backup(void);
struct termios*			term_raw(void);
void					init_line(t_edit *line_e);
t_edit					*st_line(void);

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
uint         			get_line_height(t_edit *line);

/*
**  Line edition - Autocompletion
*/

#define AUTOCOMP_ESCAPED_CHARS				("*\\'\"!? ~$")
#define AUTOCOMP_ESCAPED_CHARS_IN_DBLQUOTE	("\\\"!$")
#define AUTOCOMP_TYPE_SYMLINK			-2
#define AUTOCOMP_TYPE_CHARACTER_FILE	2
#define AUTOCOMP_TYPE_FOLDER			4
#define AUTOCOMP_TYPE_BLOCK_FILE		6
#define AUTOCOMP_TYPE_FOLDER2			8

t_file					*build_completion_list(char *str, int len, char **env,
						unsigned int *list_size);
t_file					*build_completion_list_files(char *str, int len,
						unsigned int *list_size);
void					print_comp_list(t_edit *line_e, int highlight);
int						get_last_common_char(t_file *list);
int						build_list_from_word(t_edit *line_e);
void					replace_word(t_edit *line_e, char *new, size_t length, char *suffix);
void					replace_word_from_completion(t_edit *line_e);
char					*escape_name(char *name, char* escaped_chars, unsigned int length);
char 					*escape_singlequote(char *name, unsigned int max);

/*
**  Line edition - Autocompletion parser
*/
char					*get_autocompletion_word(t_edit *line_e, unsigned int *argument, unsigned int *autocompletion_point);
int						quote_match(char *line, unsigned int *i, unsigned int maxlen, char c);
int						get_idx_quote_type(char *line, unsigned int idx);
int						is_separator(char c);
/*
**  Line edition - File list
*/


t_file					*ft_file_list_append(t_file **list, char *name, int type);
t_file					*ft_file_list_at(t_file *list, unsigned int idx);
t_file					*ft_file_list_create(char *name, int type);
void					ft_file_list_delete(t_file **list);
t_file					*merge_sort(t_file *p);

/*
** Line Lexing
*/

t_token					*get_next_token(const char **line, unsigned int *i);
t_token					*get_heredoc(t_edit *line_e, int *begin);
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

t_ast					*ast_new(t_token *tok);
void					ast_insert_left(t_token *tok, t_ast **root);
void					ast_insert_right(t_token *tok, t_ast **root);
void					infix_print_ast(t_ast *root);
void					rm_last_leaf(t_ast **root);
int						head_of_line(t_ast *ast);

/*
** Inhibitor
*/

char    				*get_word(unsigned int *i);
int						ft_isquote_inhib(int c);
int						ft_isspace_inhib(int c);
int						for_end_word_inhib(int c);
void					extend_quotes(t_edit *line_e, char **word, unsigned int *i);
int						quote_parser(const char *line, char **word, unsigned int qt);
int     				word_parser(const char *line, char **word, int qt);
char    				*word_handling(const char *, unsigned int *, int);
int    					word_handling_prime(const char *, char **, unsigned int *, int);
void    				dollars_cmd(const char *, char **, unsigned int *);
int    					backslash(const char *, char **, unsigned int *, int qt);
int	    				backslash_end(t_edit *, unsigned int *, int *);

/*
** Tools & Co
*/


#endif
