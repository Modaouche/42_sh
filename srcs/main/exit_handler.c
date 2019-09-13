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
	(er == ER_MALLOC) ? ft_putendl_fd("memory allocation failed",\
		STDERR_FILENO) : 0;
	(er == ER_ACCES) ? ft_putendl_fd("permission denied",
		STDERR_FILENO) : 0;
	(er == ER_DBACCES) ? ft_putendl_fd("database unaccesible",\
		STDERR_FILENO) : 0;
	(er == ER_DBINFO) ? ft_putendl_fd("too few information in Database",\
		STDERR_FILENO) : 0;
	(er == ER_FORK) ? ft_putendl_fd("fork failed", STDERR_FILENO) : 0;
	(er == ER_EXECVE) ? ft_putendl_fd("execve failed", STDERR_FILENO) : 0;
	(er == ER_PIPE) ? ft_putendl_fd("pipe failed", STDERR_FILENO) : 0;
	(er == ER_ISDIR) ? ft_putendl_fd("is a directory", STDERR_FILENO) : 0;
	(er == ER_NOENT) ? ft_putendl_fd("command not found", STDERR_FILENO) : 0;
	(er == ER_NOT_TTY) ? ft_putendl_fd("not a tty", STDERR_FILENO) : 0;
}

static void	le_free(t_edit *line_e)
{
	if (!line_e)
		return ;
	ft_strdel(&(line_e->line));
	if (line_e->autocomp_list)
		ft_file_list_delete(&(line_e->autocomp_list));
	ft_memdel((void **)&line_e);
}

void	to_exit(uint8_t bt)
{
	//ajouter free :... a voir
	if (bt == 1)
		g_shell.errorno = ER_MALLOC;
	error_msg("./42sh");
	le_free(g_shell.line_e);
	ast_free(&(g_shell.ast));
	free_jobs();
	free_tabstr(&(g_shell.envp));
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
		ft_putendl_fd("\n./42sh : line edition : fail\n", STDERR_FILENO);
	le_free(g_shell.line_e);
	ast_free(&(g_shell.ast));
	free_jobs();
	free_tabstr(&(g_shell.envp));
	exit(EXIT_FAILURE);
}
