/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 11:41:46 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/11 22:16:58 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

struct termios			*term_backup(void)
{
	static struct termios	termiold;

	if (tcgetattr(STDERR_FILENO, &termiold) == -1)
		le_exit(0);
	return (&termiold);
}

struct termios			*term_raw(void)
{
	static struct termios	termios;

	if (tcgetattr(STDERR_FILENO, &termios) == -1)
		le_exit(0);
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
	ft_bzero(&g_shell, sizeof(g_shell));
	ft_bzero(line_e, sizeof(line_e));
	if (!isatty(STDERR_FILENO))
		le_exit(ER_NOT_TTY);
	g_shell.fd = STDERR_FILENO;
	g_shell.pid = getpgrp();//tocheck
	while (tcgetpgrp(g_shell.fd) != g_shell.pid)
		kill(-g_shell.pid, SIGTTIN);
	signal_handler(REGULAR);
	g_shell.pid = getpid();
	setpgid(g_shell.pid, g_shell.pid);//tocheck
	tcsetpgrp(g_shell.fd, g_shell.pid);//tocheck
	line_e = st_line();
	init_line(line_e);
	fill_token_tab();
	g_shell.tc_onoff = (init_tc() == -1) ? 1 : 0;//set off termcaps
	g_shell.envp = envp;
	g_shell.termiold = term_backup();
	g_shell.termios = term_raw();

}
