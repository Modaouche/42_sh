/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:49:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/02 14:36:26 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "signal_handler.h"

static void		prompt(int sig)
{
	t_edit *line_e;

	(void)sig;
	line_e = st_line();
	cancel_autocompletion(line_e);// is it ok kicausse ?
	init_line(line_e);// is it ok kicausse ?
	ft_nlcr();
	print_prompt(0);
}

static void		le_resume(int sig)
{
	t_edit *line_e;

	(void)sig;
	line_e = st_line();
	write(1, "\n", 1);
	print_prompt(0);
	(tcgetattr(STDERR_FILENO, g_shell.termiold) == -1)\
		? toexit(0, "tcgetattr", 0) : 0;
	(tcsetattr(STDERR_FILENO, TCSADRAIN, g_shell.termios) == -1)\
		? toexit(0, "tcsetattr", 0) : 0;
	print_line(line_e, 0);// is it ok kicausse ?
	signal(SIGCONT,	le_resume);
}

static void		window_resize(int sig)
{
	t_edit *line_e;
	struct 	winsize size;

	(void)sig;
	line_e = st_line();
	ioctl(0, TIOCGWINSZ, &size);
	line_e->winsize_col = size.ws_col;
	line_e->winsize_row = size.ws_row;
}

void			signal_handler(uint8_t state)
{
	if (state == LINE_EDIT)
	{
		signal(SIGCONT,	le_resume);
		signal(SIGINT,	prompt);
		signal(SIGWINCH, window_resize);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGCONT,	SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGWINCH, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);//maybe tochange when we exec or to handle jobs
}
