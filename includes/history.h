/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 01:10:02 by araout            #+#    #+#             */
/*   Updated: 2019/08/30 12:28:11 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "shell.h"
# define GASI get_argument_starting_index

typedef struct			s_hnode
{
	char		*cmd;
}						t_hnode;

typedef struct			s_history
{
	unsigned int		line;
	t_list				*hist;
	int					fd;
	char				*path;
	off_t				size;
}						t_history;

typedef struct			s_fc
{
	int		a;
	int		b;
	char	**hist;
	int		options;
	char	**args;
}						t_fc;

/*
** history functions
*/

t_list					*build_hist_lst(void);
int						ft_history_rev(void);
void					del_hist(void);
int						get_hist_nbline(void);
void					free_history(void);
char					*double_bang(void);
int						dump_history(void);
int						ft_history(void *ptr);
void					init_history(void);
void					write_history(char *line);
int						build_node(char *line, t_list **node);
off_t					get_hist_size(void);
char					*get_hist_line_from_end(int position);
char					*get_hist_line_from_str(char *str);

/*
** ft_option funcitons
*/

int						count_args(char **args);
char					validate_options(char **args, char *valid_options);
int						get_options(char **args);
int						get_argument_starting_index(char **args,\
		char force_letter);
int						get_option(int options, char letter);

/*
** fc functions
*/

int						check_head(t_list *head, char **ret);
char					**get_history_field(int a, int b, char **ret, int rev);
int						get_range(char **args, int *a, int *b, int i);
int						valid_operand(char **args, int i);
int						get_field_size(char **field);
int						ft_fc(void *ptr);
void					print_rev(char **field, int a, int b, int flag);
void					print_field(char **field, int a, int b, int flag);
int						print_history(int flag, char **field, int a, int b);
void					set_a_b_under_zero(int *a, int *b);
int						get_index_fc_by_string(char *arg);
int						exec_fc_s(char **args, char *line, int index);
int						get_index_fc_by_string(char *arg);
void					edit_line(char **hist, char *editor);
void					exec_file(char *filename);
int						free_fc(t_fc *fc_struct);
#endif
