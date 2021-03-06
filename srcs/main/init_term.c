/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 11:41:46 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 09:19:21 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#define DEFAULT_TERM "xterm-256color"

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

static int				init_tc(void)
{
	char		*term_type;
	int			ret;

	if (!(term_type = getenv("TERM")))
		return (-1);
	ret = tgetent(NULL, getenv("TERM"));
	if (ret == 1 && ft_strcmp("dumb", getenv("TERM")))
		return (0);
	g_shell.errorno = (ret > 0 && ft_strcmp("dumb", getenv("TERM")))
		? ER_DBACCES : ER_DBINFO;
	error_msg("42sh");
	return (-1);
}

void					init_term(t_edit *line_e, char **envp)
{
	ft_bzero(&g_shell, sizeof(g_shell));
	ft_bzero(line_e, sizeof(line_e));
	g_shell.fd = STDERR_FILENO;
	if (!(g_shell.is_interactive = isatty(g_shell.fd)))
		le_exit(ER_NOT_TTY);
	init_env(envp);
	if (init_tc() == -1)
		g_shell.envp = set_var_env("TERM", DEFAULT_TERM, g_shell.envp);
	g_shell.pid = getpgrp();
	while (tcgetpgrp(g_shell.fd) != g_shell.pid)
		kill(-g_shell.pid, SIGTTIN);
	signal_handler(REGULAR);
	g_shell.pid = getpid();
	setpgid(g_shell.pid, g_shell.pid);
	tcsetpgrp(g_shell.fd, g_shell.pid);
	line_e = st_line();
	init_line(line_e);
	fill_token_tab();
	g_shell.termiold = term_backup();
	g_shell.termios = term_raw();
	g_shell.in_fg = true;
	init_history();
	g_shell.fptr = init_fptr();
}
