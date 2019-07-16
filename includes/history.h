	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 01:10:02 by araout            #+#    #+#             */
/*   Updated: 2019/07/16 05:27:19 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "shell.h"

typedef struct			s_hnode
{
	char		*cmd;
	int			index;
}						t_hnode;

typedef struct			s_history
{
	unsigned int		line;
	t_list				*hist;
	int					fd;
	char				*path;
	off_t				size;
}						t_history;

void					free_history(void);
char					*double_bang(void);
int						dump_history(void);
int						ft_history(void *ptr);
void					init_history(void);
void					write_history(char *line);
int						build_node(char *line, t_list **node);
#endif
