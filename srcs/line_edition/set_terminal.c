/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_terminal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 11:41:46 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/11 22:16:58 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

struct termios				*term_backup(void)
{
	static struct termios	termiold;

	if (tcgetattr(STDERR_FILENO, &termiold) == -1)
		toexit(0, "tcgetattr", 1);
	return (&termiold);
}

struct termios				*term_raw(void)
{
	static struct termios	termios;

	if (tcgetattr(STDERR_FILENO, &termios) == -1)
		toexit(0, "tcgetattr", 1);
	termios.c_lflag |= IEXTEN;
	termios.c_lflag &= ~(ICANON | ECHO);
	termios.c_oflag &= ~(OPOST);
	termios.c_cc[VTIME] = 0;
	termios.c_cc[VMIN] = 1;
	return (&termios);
}

void						set_terminal(t_edit *line_e)
{
	line_e->termiold = term_backup();
	line_e->termios = term_raw();
	line_e->len_max = BUFFER_LEN;
	if (!isatty(STDERR_FILENO))
		toexit(line_e, "isatty", 1);
}
