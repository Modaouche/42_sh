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
	if (g_shell.buff_cmd)
		ft_printf_fd(STDERR_FILENO, "%s : ",g_shell.buff_cmd[0]);
	if (er == ER_SYNTAX)
		ft_printf_fd(STDERR_FILENO, "Parse error near `%s'\n",\
			g_shell.buff_cmd[0]);
	(er == ER_MALLOC) ? ft_putstr_fd("Memory allocation failed\n",\
		STDERR_FILENO) : 0;
	(er == ER_ACCES) ? ft_putstr_fd("Permission denied\n",
		STDERR_FILENO) : 0;
	(er == ER_DBACCES) ? ft_putstr_fd("Database unaccesible\n",\
		STDERR_FILENO) : 0;
	(er == ER_DBINFO) ? ft_putstr_fd("too few information in Database\n",\
		STDERR_FILENO) : 0;
	(er == ER_FORK) ? ft_putstr_fd("Fork failed\n", STDERR_FILENO) : 0;
	(er == ER_EXECVE) ? ft_putstr_fd("Execve failed\n", STDERR_FILENO) : 0;
	(er == ER_PIPE) ? ft_putstr_fd("Pipe failed\n", STDERR_FILENO) : 0;
	(er == ER_ISDIR) ? ft_putstr_fd("Is a directory\n", STDERR_FILENO) : 0;
	(er == ER_NOT_TTY) ? ft_putstr_fd("Not a tty\n", STDERR_FILENO) : 0;
}

void	to_exit(uint8_t bt)
{
	//ajouter free : line_e_free, ast_free, process_free,...
	if (bt == 1)
		g_shell.errorno = ER_MALLOC;
	error_msg("\n.42sh : ");
	if (g_shell.buff_cmd)
		free_tabstr(&(g_shell.buff_cmd));
	exit(EXIT_FAILURE);
}

void	le_exit(uint8_t bt)
{
	//ajouter free : line_e_free, ast_free, process_free,...
	if (g_shell.termiold)
		tcsetattr(STDERR_FILENO, TCSAFLUSH, g_shell.termiold);
	if ((g_shell.errorno = bt))
		error_msg("\n./42sh : ");
	else
		ft_putstr_fd("\n./42sh : line edition : fail\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
