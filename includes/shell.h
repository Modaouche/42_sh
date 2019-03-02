/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:26:51 by modaouch          #+#    #+#             */
/*   Updated: 2019/03/02 10:54:30 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <term.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <curses.h>
//# include <stdio.h>

unsigned int     g_errorno;

# define ER_DBACCES	    	1
# define ER_DBINFO	    	2

# define S_KEY_ARW_LEFT		0
# define S_KEY_ARW_RIGHT	0
# define S_KEY_ARW_BOT		0
# define S_KEY_ARW_TOP		0
# define S_KEY_ERASE		0
# define S_KEY_PRINTABLE	0
# define S_KEY_SPACE		0
# define S_KEY_ESC			27
# define S_KEY_RET			10
# define S_KEY_CTRL_D		4
# define S_KEY_END			1
# define S_KEY_NONE			0

# define MAX_KEY_LEN		15
# define BUFFER_LEN			255

typedef struct			s_edit
{
	struct termios		*termiold;
	struct termios		*termios;
	struct winsize		*wsize;
    char                *line;
	unsigned int		cursor_pos;
	unsigned int		len_max;
	char				tc_onoff;
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
struct termios			*term_backup(int bt);
struct termios			*term_raw(int bt);

/*
** Line edition
*/

int						line_edition(t_edit *line_e);
void					cursor_reposition(size_t n);
int						is_arrow(char *key);
int						ft_puti(int i);
void					ft_nlcr(void);

/*
** Tools & Co
*/


#endif
