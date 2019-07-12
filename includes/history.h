/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 01:10:02 by araout            #+#    #+#             */
/*   Updated: 2019/07/12 03:15:44 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "shell.h"

typedef struct			s_history
{
	unsigned int		line;
	char				**history;
	int					fd;
	char				*path;
	off_t				offset_end;
}						t_history;

void					free_history(void);
char					*double_bang(void);
int						dump_history(char ***ret);
int						ft_history(void *ptr);
void					init_history(void);
void					write_history(char *line);
int						get_hist_line(void);
#endif
