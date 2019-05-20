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

void	toexit(t_edit *line_e, char *str)
{
	if (line_e && line_e->termiold)
	{
		line_e->termiold->c_lflag |= (ICANON | ECHO);
		line_e->termiold->c_oflag |= (OPOST);
		tcsetattr(STDERR_FILENO, TCSAFLUSH, line_e->termiold);
	}
	ft_putstr_fd("./ft_select : ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(" : failed", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
