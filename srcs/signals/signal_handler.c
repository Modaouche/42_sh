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
	init_line(line_e);//a voir avec kicausse
	ft_nlcr();
	tputs(tgetstr("cd", NULL), 1, ft_puti);
	print_prompt(0);
}

static void		le_resume(int sig)
{
	t_edit *line_e;

	(void)sig;
	line_e = st_line();
	write(1, "\n", 1);
	print_prompt(0);
	ft_putstr(line_e->line);//to check if it work
	(tcgetattr(STDERR_FILENO, g_shell.termiold) == -1)\
		? toexit(0, "tcgetattr", 0) : 0;
	(tcsetattr(STDERR_FILENO, TCSADRAIN, g_shell.termios) == -1)\
		? toexit(0, "tcsetattr", 0) : 0;
	signal(SIGCONT,	le_resume);
}

void			signal_handler(uint8_t state)
{
	if (state == LINE_EDIT)
	{
		signal(SIGCONT,	le_resume);
		signal(SIGINT,	prompt);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGCONT,	SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);//maybe tochange when we exec or to handle jobs
}
