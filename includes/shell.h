/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:26:51 by modaouch          #+#    #+#             */
/*   Updated: 2019/07/06 17:40:34 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <term.h>
# include <curses.h>
# include "libft.h"
# include <stdbool.h>
# include "token_and_ast.h"
# include "signal_handler.h"
# include <fcntl.h>
# include <errno.h>// to remove

# define S_KEY_ARW_UP			65
# define S_KEY_ARW_DOWN			66
# define S_KEY_ARW_RIGHT		67
# define S_KEY_ARW_LEFT			68
# define S_KEY_ENTER			10
# define S_KEY_ERASE			127

/*
** # define S_KEY_PRINTABLE		0
** # define S_KEY_SPACE			0
** # define S_KEY_ESC			27
** # define S_KEY_CTRL_D		4
** # define S_KEY_END			1
** # define S_KEY_NONE			0
*/
# define MAX_KEY_LEN			12
# define BUFFER_LEN				255
# define TAB_LEN				7
# define TAB_CHARS				"       "

# define TOKEN_CMP			";\n&|!<>"
# define BKSH_DQT_CMP			"\\$\"\'"

typedef enum
{
	NO_ERROR,
	ER_DBACCES,
	ER_DBINFO,
	ER_SYNTAX
}	t_errorno;

typedef struct			s_file
{
	char				*name;
	size_t				len;
	int					type;
	struct s_file		*next;
}						t_file;

typedef struct			s_edit
{
	struct winsize		*wsize;
	char				*line;
	t_file				*autocomp_list;
	int					autocomp;
	unsigned int		autocomp_idx;
	unsigned int		autocomp_size;
	unsigned int		autocomp_point;
	unsigned int		autocomp_maxcol;
	unsigned int		autocomp_maxrow;
	unsigned int		autocomp_quote;
	unsigned int		len;
	unsigned int		ofst;
	unsigned int		cursor_pos;
	unsigned int		len_max;
	unsigned int		winsize_col;
	unsigned int		winsize_row;
}						t_edit;

typedef struct			s_sh
{
	struct termios		*termiold;
	struct termios		*termios;
	char				**envp;
	t_ast				*ast;
	char				**buff_cmd;
	bool				tc_onoff;//for termcap like "dumb" , to have a usable shell
	bool				in_bg;
	pid_t				pid;
	uint16_t			fd;
	uint8_t				prompt_size;
	uint8_t				errorno;
	char				*hist_path;
}						t_sh;

t_sh					g_shell;

/*
** Initialization & Co
*/

void					init_term(t_edit *line_e, char **envp);
void					toexit(t_edit *line_e, char *str, int err);
struct termios			*term_backup(void);
struct termios			*term_raw(void);
void					init_line(t_edit *line_e);
t_edit					*st_line(void);
t_ast_ptr				*st_ast(void);

/*
** Line edition
*/

int						line_edition(t_edit *line_e);
void					cursor_reposition(size_t n);
int						is_arrow(char *key);
int						ft_puti(int i);
void					ft_nlcr(void);
size_t					print_prompt(uint btn);
void					cursor_start(t_edit *line_e);
void					cursor_end(t_edit *line_e);
void					cursor_after(t_edit *line_e);
void					cursor_move_to(t_edit *line_e, uint pos);
void					cursor_move_from_to(t_edit *line_e, uint from, uint to);
void					cursor_reset_x_pos(t_edit *line_e);
uint					get_line_height(t_edit *line, uint end);
uint					get_index_x_pos(t_edit *line_e, uint pos);
void					print_line(t_edit *line_e, unsigned int start);

/*
**  Line edition - Autocompletion
*/

# define AUTOCOMP_ESCAPED_CHARS			("*\\'\"!? ~$")
# define AUTOCOMP_ESCAPED_CHARS_IN_DBLQUOTE	("\\\"!$")
# define AUTOCOMP_TYPE_SYMLINK			-2
# define AUTOCOMP_TYPE_CHARACTER_FILE		2
# define AUTOCOMP_TYPE_FOLDER			4
# define AUTOCOMP_TYPE_BLOCK_FILE		6
# define AUTOCOMP_TYPE_FOLDER2			8

t_file					*build_completion_list(int *cont, char *str, int len, char **env,\
					unsigned int *list_size);
t_file					*build_completion_list_files(int *cont, char *str, int len,\
					unsigned int *list_size);
void					print_comp_list(t_edit *line_e, int highlight);
int						get_last_common_char(t_file *list);
int						build_list_from_word(t_edit *line_e);
void					replace_word(t_edit *line_e, char *new,\
						size_t length, char *suffix);
void					replace_word_from_completion(t_edit *line_e);
char					*escape_name(char *name, char *escaped_chars,\
						unsigned int length);
char					*escape_singlequote(char *name, unsigned int max);
int						search_similar_env_var(int *cont, t_file **list, char *str,\
					int len, char **env);
void					cancel_autocompletion(t_edit *line_e);

/*
**  Line edition - Autocompletion parser
*/

char					*get_autocompletion_word(t_edit *line_e,\
					unsigned int *argument,\
					unsigned int *autocompletion_point);
int						quote_match(char *line, unsigned int *i,\
					unsigned int maxlen, char c);
int						get_idx_quote_type(char *line, unsigned int idx);
int						is_separator(char c);

/*
**  Line edition - File list
*/

t_file					*ft_file_list_append(t_file **list, char *name,
		int type);
t_file					*ft_file_list_at(t_file *list, unsigned int idx);
t_file					*ft_file_list_create(char *name, int type);
void					ft_file_list_delete(t_file **list);
t_file					*merge_sort(t_file *p);

/*
** Line Lexing
*/

t_token					*get_next_token(char **line, unsigned int *i);
t_token					*get_heredoc(t_edit *line_e);
int						line_lexer(t_edit *line_e);
void					skip_predicat(char **line, unsigned int *i,\
		int (*pred)(int));
int						wordlen(char *line);
int						ft_isspace_tok(int c);
int						isassign(int c);
void					fill_token_tab(void);
void					token_isword(t_token *actual_token, char *line,\
		unsigned int *i);
void					token_isio_nb(t_token *actual_token, char *line,\
		unsigned int *i);
unsigned int			token_isassignmt(t_token *actual_token, char *line,\
		unsigned int *i);
void					token_iseof(t_token *actual_token, char *line,\
		unsigned int *i);
void					token_isnewl(t_token *actual_token, char *line,\
		unsigned int *i);
void					token_isbang(t_token *actual_token, char *line,\
		unsigned int *i);
void					token_issemi(t_token *actual_token, char *line,\
		unsigned int *i);
void					token_isamper(t_token *actual_token, char *line,\
		unsigned int *i);
void					token_isand(t_token *actual_token, unsigned int *i);
void					token_isor(t_token *actual_token, unsigned int *i);
void					token_ispipe(t_token *actual_token, char *line,\
		unsigned int *i);
void					token_isgreat(t_token *actual_token, char *line,\
		unsigned int *i);
void					token_isdgreat(t_token *actual_token, unsigned int *i);
void					token_isclobber(t_token *actual_token,\
		unsigned int *i);
void					token_isgreatand(t_token *actual_token,\
		unsigned int *i);
void					token_isless(t_token *actual_token, char *line,\
		unsigned int *i);
void					token_isdless(t_token *actual_token, char *line,\
		unsigned int *i);
void					token_isdlessdash(t_token *actual_token,\
		unsigned int *i);
void					token_islessgreat(t_token *actual_token,\
		unsigned int *i);
void					token_islessand(t_token *actual_token, unsigned int *i);

/*
** Parsing
*/

void					line_parser(t_edit *line_e);
void					complet_cmd(t_edit *line_e);
void					list_fct(t_edit *line_e);
void					list_prime_fct(t_edit *line_e);
void					list_dprime_fct(t_edit *line_e);
void					and_or_fct(t_edit *line_e);
void					and_or_prime_fct(t_edit *line_e);
void					and_or_op_fct(t_edit *line_e);
void					bang_fct(t_edit *line_e);
void					pipeline_fct(t_edit *line_e);
void					pipe_sequence_fct(t_edit *line_e);
void					pipe_sequence_prime_fct(t_edit *line_e);
void					command_fct(t_edit *line_e);
void					cmd_suffix_fct(t_edit *line_e);
void					cmd_suffix_opt_fct(t_edit *line_e);
void					cmd_suffix_prime_fct(t_edit *line_e);
void					cmd_suffix_dprime_fct(t_edit *line_e);
void					cmd_prefix_fct(t_edit *line_e);
void					cmd_prefix_prime_fct(t_edit *line_e);
void					io_redirect_fct(t_edit *line_e);
void					io_number_opt_fct(t_edit *line_e);
void					io_kind_fct(t_edit *line_e);
void					io_file(t_edit *line_e);
void					io_here(t_edit *line_e);
void					line_break_fct(t_edit *line_e);
void					separator_op_fct(t_edit *line_e);
void					newline_list_fct(t_edit *line_e);
void					newline_list_prime_fct(t_edit *line_e);
bool					token_cmp(int kind, ...);

/*
** Abstract Syntax Tree
*/

t_ast					*ast_new(t_token *tok);
void					ast_left_insert(t_token *tok);
void					ast_right_insert(t_token *tok);
void					ast_next_cmd(t_token *tok);
void					infix_print_ast(t_ast *node);
void					rm_last_leaf(void);
int						last_token(t_ast *node);
t_ast					*last_node(t_ast *node);
void					bind_last_head(void);
void					assign_to_word(void);
t_ast					*get_curr_head(void);

/*
** Line Execution
*/
void					line_execution(void);
void					ast_execution(t_ast *ast);
bool					exec_and_or(t_ast *ast);
bool					exec_cmd(t_ast *ast);
bool					exec_redir(t_ast *ast);
bool					is_slice_exec(t_tok tokind);
bool					is_and_or_exec(t_tok tokind);
bool					is_redir_pipe_exec(t_tok tokind);

/*
** Inhibitor
*/

char					*get_word(unsigned int *i);
int						ft_isquote_inhib(int c);
int						ft_isspace_inhib(int c);
int						for_end_word_inhib(int c);
void					extend_quotes(t_edit *line_e, char **word,\
		unsigned int *i);
int						quote_parser(const char *line, char **word,\
		unsigned int qt);
int						word_parser(const char *line, char **word, int qt);
char					*word_handling(const char *line, unsigned int *i,\
		int qt);
int						word_handling_prime(const char *line, char **word,\
		unsigned int *i, int qt);
void					dollars_cmd(const char *line, char **word,\
		unsigned int *qt);
int						backslash(const char *line, char **word,
		unsigned int *i, int qt);
int						backslash_end(t_edit *line_e, unsigned int *i, int *qt);

/*
** history
*/
void					open_history(void);
void					write_history(char *line);
char					**dump_history(void);
#endif
