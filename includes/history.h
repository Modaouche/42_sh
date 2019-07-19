	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 01:10:02 by araout            #+#    #+#             */
/*   Updated: 2019/07/18 07:50:11 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "shell.h"

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
int						ft_fc(void *ptr);
off_t					get_hist_size(void);


int		count_args(char **args);
char	validate_options(char **args, char *valid_options);
int		get_options(char **args);
int		get_argument_starting_index(char **args, char force_letter);
int		get_option(int options, char letter);

#endif
