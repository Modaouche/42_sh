/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:26:51 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 12:25:46 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <term.h>
# include <curses.h>
# include "libft.h"
# include <stdbool.h>
# include <sys/wait.h>
# include "token_and_ast.h"
# include "signal_handler.h"
# include <fcntl.h>
# include <sys/mman.h>
# define _GNU_SOURCE

/*
**# include <errno.h> to remove
*/
# include "env.h"
# include "history.h"
# include "built_in.h"
# include "error_handler.h"
# include "job.h"
# include "param_expansion.h"
# include "tild.h"

# define S_KEY_ARW_UP			65
# define S_KEY_ARW_DOWN			66
# define S_KEY_ARW_RIGHT		67
# define S_KEY_ARW_LEFT			68
# define S_KEY_ENTER			10
# define S_KEY_ERASE			127
# define S_KEY_CTRL_D			4

/*
** # define S_KEY_PRINTABLE		0
** # define S_KEY_SPACE			0
** # define S_KEY_ESC			27
** # define S_KEY_END			1
** # define S_KEY_NONE			0
*/

# define MAX_KEY_LEN			12
# define BUFFER_LEN				255
# define TAB_LEN				7
# define TAB_CHARS				"       "

# define TOKEN_CMP				";\n&|!<>"
# define BKSH_DQT_CMP			"\\$\"\'"

typedef struct			s_file
{
	char				*name;
	size_t				len;
	int					type;
	struct s_file		*next;
}						t_file;

typedef struct			s_fptr
{
	char				**flag;
	int					(*f[255])(char **);
}						t_fptr;

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
	unsigned int		history_pos;
	unsigned int		len;
	unsigned int		ofst;
	unsigned int		cursor_pos;
	unsigned int		len_max;
	unsigned int		winsize_col;
	unsigned int		winsize_row;
	int					search_mode;
}						t_edit;

/*
** struct  s_sh
** tc_onoff = for termcap like "dumb",to have a usable shell
**	in_bg = in proc struct
*/

typedef struct			s_sh
{
	struct termios		*termiold;
	struct termios		*termios;
	char				**envp;
	char				**aliasp;
	char				**intern_var;
	t_edit				*line_e;
	t_ast				*ast;
	char				**buff_cmd;
	pid_t				pid;
	t_job				*first_job;
	uint16_t			fd;
	uint16_t			redir_fd[10];
	uint8_t				prompt_size;
	uint8_t				errorno;
	bool				tc_onoff;
	bool				in_bg;
	bool				isnt_interactive;
	struct s_history	*history;
	uint16_t			is_interactive;
	uint8_t				ret;
	bool				in_fg;
	t_fptr				*fptr;
}						t_sh;

extern t_sh					g_shell;

typedef struct			s_cmd_verif_prime
{
	char				*path_var;
	char				**sliced_path;
	char				*to_check;
	int					idx;
}						t_cmd_verif_prime;

typedef struct			s_io_here
{
	t_token				*heredoc;
	char				*cpy;
	t_token				*to_cmp;
	int					begin;
	t_ast				*next;
}						t_io_here;

typedef struct			s_parse_word
{
	char				*str;
	unsigned int		i;
	unsigned int		x;
	unsigned int		escape;
}						t_parse_word;

typedef struct			s_autocomp_word
{
	unsigned int		i;
	unsigned int		word_start;
	unsigned int		word_end;
	unsigned int		escape;
	unsigned int		word_idx;

}						t_autocomp_word;

typedef struct			s_a
{
	unsigned int		i;
	unsigned int		quote;
	unsigned int		escape;
}						t_a;

typedef struct			s_comp_print
{
	int					i;
	unsigned int		column;
	unsigned int		column_end;
	unsigned int		maxcol;
	unsigned int		maxrow;
	unsigned int		max_length;
	unsigned int		page;
	unsigned int		maxpage;
	unsigned int		newlines;
	unsigned int		window_maxrow;
}						t_comp_print;

typedef struct			s_word_mov
{
	unsigned int		i;
	unsigned int		word_start;
	unsigned int		last_word_start;
	unsigned int		escape;
	unsigned int		quote;
}						t_word_mov;

typedef struct			s_dup_wspc
{
	unsigned int		i;
	bool				escape;
	int					count;
	int					whitespace_count;
}						t_dup_wspc;

/*
** Initialization & Co
*/

void					init_term(t_edit *line_e, char **envp);
struct termios			*term_backup(void);
struct termios			*term_raw(void);
void					init_line(t_edit *line_e);
t_edit					*st_line(void);
t_ast_ptr				*st_ast(void);
t_fptr					*init_fptr(void);
void					free_for_ft_built_in(t_fptr *func);

/*
** Line edition
*/

void					start_autocomp(t_edit *line_e, char *prevkey);
void					arrows_handler(t_edit *line_e, char *key);
void					replace_line_with_search(t_edit *line_e);
void					change_autocomp_idx(t_edit *line_e, int value);
void					get_hist_line(t_edit *line_e, int offset);
void					on_key_press(t_edit *line_e, char *prevkey, char *key);
void					go_to_next_line(t_edit *line_e);
void					go_to_prev_line(t_edit *line_e);
void					go_to_next_word(t_edit *line_e);
void					go_to_prev_word(t_edit *line_e);
int						can_insert_tabs(t_edit *line_e);
void					insert_char(t_edit *line_e, char c);
int						get_last_dollar(t_edit *line_e, unsigned int word_start,
							unsigned int word_end);
void					remove_duplicate_whitespaces(t_edit *line_e);
void					re_print_prompt(t_edit *line_e);
void					re_print_line(t_edit *line_e);
int						line_edition(t_edit *line_e);
int						is_arrow(char *key);
int						ft_puti(int i);
void					ft_nlcr(void);
size_t					print_prompt(uint btn);
void					cursor_start(t_edit *line_e);
void					cursor_end(t_edit *line_e);
void					cursor_after(t_edit *line_e);
void					cursor_move_to(t_edit *line_e, uint pos);
void					cursor_move_from_to(t_edit *line_e, uint from, uint to);
void					cursor_move_from_to2(int prefix,\
							char *str, uint from, uint to);
void					cursor_reset_x_pos(t_edit *line_e);
uint					get_line_height(t_edit *line, uint end);
uint					get_str_height(t_edit *line_e, unsigned int prefix,\
							char *str, unsigned int end);
uint					get_index_x_pos(t_edit *line_e, uint pos);
void					print_line(t_edit *line_e, unsigned int start);
void					show_hist_line(t_edit *line_e);
void					le_free(t_edit *line_e);
void					replace_word_with_alias(t_edit *line_e, char *alias,\
							char *value);
unsigned int			search_similar_files(t_file **list, char *path,
							char *str, int len);
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

int						get_last_slash(t_edit *line_e, unsigned int word_start,
							unsigned int word_end);
t_file					*build_completion_list(char *str, int len,\
							unsigned int *list_size);
t_file					*build_completion_list_files(char *str,\
							int len, unsigned int *list_size);
void					print_comp_list(t_edit *line_e, int highlight);
int						get_last_common_char(t_file *list);
int						build_list_from_word(t_edit *line_e);
void					replace_line_raw(t_edit *line_e, char *new);
void					replace_word(t_edit *line_e, char *new,\
							size_t length, char *suffix);
void					replace_word_from_completion(t_edit *line_e);
char					*escape_name(char *name, char *escaped_chars,\
							unsigned int length);
char					*escape_singlequote(char *name, unsigned int max);
int						search_similar_env_var(t_file **list,\
							char *str, int len);
void					cancel_autocompletion(t_edit *line_e);
int						get_list_longest_word(t_file *list);
void					print_with_pad(t_file *file, int minlen, int selected,
							unsigned int win_maxlen);
int						search_similar_builtin_aliases(t_file **list,
							char *str, int len);

/*
**  Line edition - Autocompletion parser
*/

char					*parse_word(char *line, unsigned int end);
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

t_file					*ft_file_list_append(t_file **list, char *name,\
							int type);
t_file					*ft_file_list_at(t_file *list, unsigned int idx);
t_file					*ft_file_list_create(char *name, int type);
void					ft_file_list_delete(t_file **list);
t_file					*merge_sort(t_file *p);

/*
** Line Lexing
*/

char					**get_assignments(t_ast *ast);
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
void					ast_free(t_ast **root);
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
bool					exec_cmd(t_ast *ast, bool to_fork);
bool					exec_redir(t_ast *ast);
bool					is_slice_exec(t_tok tokind);
bool					is_and_or_exec(t_tok tokind);
bool					is_redir_exec(t_tok tokind);
bool					is_other_exec(t_tok tokind);
bool					exec_builtin(char **args);
bool					is_builtin(char *bu);
char					**get_cmd(t_ast *ast);
bool					cmds_verif(t_process *p, char **envp);
bool					access_verification(char *cmd);
char					*find_var(char **envp, char *with);
char					*generate_random_filename(char *prefix);

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
void					insert_home_path(const char *line, char **word,
							unsigned int *i);
void					expand_brackets(const char *line,\
							char **word, unsigned int *i);
void					insert_env_var_value(const char *line, char **word,\
							unsigned int *i);

/*
** Alias
*/
void					replace_aliases(t_edit *line_e);

#endif
