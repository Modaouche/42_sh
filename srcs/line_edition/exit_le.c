/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_le.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 11:57:20 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/06 18:19:03 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//cree une fct perror(int g_errorno) like 

void	toexit(t_edit *line_e, char *str, int err)
{
	if (line_e && g_shell.termiold)//tochange
	{
	//	g_shell.termiold->c_lflag |= (ICANON | ECHO);
	//	g_shell.termiold->c_oflag |= (OPOST);
		tcsetattr(STDERR_FILENO, TCSAFLUSH, g_shell.termiold);
	}
	ft_putstr_fd("\n./42sh : ", STDERR_FILENO);
	if (err)
		perror(str);//to rm ?
	else
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(" : failed", STDERR_FILENO);
	}
	exit(EXIT_FAILURE);
}//tochange avec des free et rename en le_exit
