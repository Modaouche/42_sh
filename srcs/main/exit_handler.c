/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:57:20 by modaouch          #+#    #+#             */
/*   Updated: 2019/07/04 18:19:03 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		error_msg(char *cmd)
{
	uint8_t er;

	er = g_shell.errorno;
	ft_printf_fd(STDERR_FILENO, "\n%s : ", cmd);
	(er == ER_SYNTAX) ? ft_printf_fd(STDERR_FILENO,\
			"parse error near `%s'.",g_shell.buff_cmd[0]) : 0;
	(er == ER_MALLOC) ? ft_putstr_fd("memory allocation failed.",\
		STDERR_FILENO) : 0;
	(er == ER_ACCES) ? ft_putstr_fd("permission denied.",
		STDERR_FILENO) : 0;
	(er == ER_DBACCES) ? ft_putstr_fd("database unaccesible.",\
		STDERR_FILENO) : 0;
	(er == ER_DBINFO) ? ft_putstr_fd("too few information in Database.",\
		STDERR_FILENO) : 0;
	(er == ER_FORK) ? ft_putstr_fd("fork failed.", STDERR_FILENO) : 0;
	(er == ER_EXECVE) ? ft_putstr_fd("execve failed.", STDERR_FILENO) : 0;
	(er == ER_PIPE) ? ft_putstr_fd("pipe failed", STDERR_FILENO) : 0;
	(er == ER_ISDIR) ? ft_putstr_fd("is a directory.", STDERR_FILENO) : 0;
	(er == ER_NOENT) ? ft_putstr_fd("command not found.", STDERR_FILENO) : 0;
	(er == ER_NOT_TTY) ? ft_putstr_fd("not a tty.", STDERR_FILENO) : 0;
}

void	to_exit(uint8_t bt)
{
	//ajouter free :...
	if (bt == 1)
		g_shell.errorno = ER_MALLOC;
	error_msg(".42sh");
	if (g_shell.buff_cmd)
		free_tabstr(&(g_shell.buff_cmd));
	le_free();
	ast_free(g_shell.ast);
	free_jobs();
	free_tabstr(g_shell.envp);
	exit(EXIT_FAILURE);
}

void	le_exit(uint8_t bt)
{
	//ajouter free : ...
	if (g_shell.termiold)
		tcsetattr(STDERR_FILENO, TCSAFLUSH, g_shell.termiold);
	if ((g_shell.errorno = bt))
		error_msg("./42sh");
	else
		ft_putstr_fd("\n./42sh : line edition : fail\n", STDERR_FILENO);
	le_free();
	ast_free(g_shell.ast);
	free_jobs();
	free_tabstr(g_shell.envp);
	exit(EXIT_FAILURE);
}

void	le_free(t_edit *line_e)
{
	ft_strdel(line_e->line);
	if (line_e->autocomp_list)
		ft_file_list_delete(&(line_e->autocomp_list));
	ft_memdel(&line_e);
}
