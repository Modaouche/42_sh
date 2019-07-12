/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 11:41:46 by modaouch          #+#    #+#             */
/*   Updated: 2019/07/12 01:39:36 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

struct termios			*term_backup(void)
{
	static struct termios	termiold;

	if (tcgetattr(STDERR_FILENO, &termiold) == -1)
		toexit(0, "tcgetattr", 1);
	return (&termiold);
}

struct termios			*term_raw(void)
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

static int		init_tc(void)
{
	char		*term_type;
	int		ret;

	if (!(term_type = getenv("TERM")))
		return (-1);
	ret = tgetent(NULL, getenv("TERM"));
	if (ret == 1 && ft_strcmp("dumb", getenv("TERM")))
		return (0);
	g_shell.errorno = (ret > 0 && ft_strcmp("dumb", getenv("TERM")))
		? ER_DBACCES : ER_DBINFO;
	return (-1);
}

void				init_term(t_edit *line_e, char **envp)
{
	if (!isatty(STDERR_FILENO))
		toexit(line_e, "isatty", 1);
	line_e = st_line();
	ft_bzero(line_e, sizeof(line_e));
	ft_bzero(&g_shell, sizeof(g_shell));
	init_line(line_e);
	fill_token_tab();
	g_shell.tc_onoff = (init_tc() == -1) ? 1 : 0;//set off termcaps
	init_env(envp);
	g_shell.fd = STDERR_FILENO;
	g_shell.termiold = term_backup();
	g_shell.termios = term_raw();
	g_shell.pid = getpgrp();//tocheck
	while (tcgetpgrp(g_shell.fd) != g_shell.pid)
	{
		ft_printf("PGRP != PID\n");
		kill(-g_shell.pid, SIGTTIN);
	}//tocheck
	signal_handler(REGULAR);
	g_shell.pid = getpid();
	setpgid(g_shell.pid, g_shell.pid);//tocheck
	tcsetpgrp(g_shell.fd, g_shell.pid);//tocheck
	init_history();
}
