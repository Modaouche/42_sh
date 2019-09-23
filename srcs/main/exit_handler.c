/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:57:20 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 09:25:08 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	error_msg_2(uint8_t er)
{
	if (er == ER_NOT_TTY)
		ft_putendl_fd("not a tty", STDERR_FILENO);
	else if (er == ER_WAITPID)
		ft_putendl_fd("waitpid failed", STDERR_FILENO);
	else
		ft_putendl_fd("unknown error", STDERR_FILENO);
}

void		error_msg(char *cmd)
{
	uint8_t er;

	er = g_shell.errorno;
	ft_printf_fd(STDERR_FILENO, "\n%s : ", cmd);
	if (er == ER_MALLOC)
		ft_putendl_fd("memory allocation failed", STDERR_FILENO);
	else if (er == ER_ACCES)
		ft_putendl_fd("permission denied", STDERR_FILENO);
	else if (er == ER_DBACCES)
		ft_putendl_fd("database unaccesible", STDERR_FILENO);
	else if (er == STDERR_FILENO)
		ft_putendl_fd("too few information in Database", STDERR_FILENO);
	else if (er == ER_FORK)
		ft_putendl_fd("fork failed", STDERR_FILENO);
	else if (er == ER_EXECVE)
		ft_putendl_fd("execve failed", STDERR_FILENO);
	else if (er == ER_PIPE)
		ft_putendl_fd("pipe failed", STDERR_FILENO);
	else if (er == ER_ISDIR)
		ft_putendl_fd("is a directory", STDERR_FILENO);
	else if (er == ER_NOENT)
		ft_putendl_fd("command not found", STDERR_FILENO);
	else
		error_msg_2(er);
}

void		le_free(t_edit *line_e)
{
	if (!line_e)
		return ;
	ft_strdel(&(line_e->line));
	if (line_e->autocomp_list)
		ft_file_list_delete(&(line_e->autocomp_list));
}

void		to_exit(uint8_t bt)
{
	g_shell.errorno = bt;
	error_msg("./42sh");
	fexit(ft_split("exit 1", " "));
}

void		le_exit(uint8_t bt)
{
	if (g_shell.termiold)
		tcsetattr(STDERR_FILENO, TCSAFLUSH, g_shell.termiold);
	if ((g_shell.errorno = bt))
		error_msg("./42sh");
	else
		ft_putendl_fd("\n./42sh : line edition : fail\n", STDERR_FILENO);
	fexit(ft_split("exit 1", " "));
}
