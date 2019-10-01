/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 06:00:02 by araout            #+#    #+#             */
/*   Updated: 2019/09/23 12:43:44 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int			get_exit_return_val(char **p)
{
	int ret;
	int j;

	j = 0;
	ret = p[1] ? ft_atoi(p[1]) : 0;
	if (p[1] && !ft_strisdigit(p[1]) && (ret = 1))
		ft_printf_fd(2, "exit: numeric argument required\n");
	else if (p[1] && p[2] && (ret = 1))
		ft_printf_fd(2, "exit: too many arguments\n");
	while (p[j])
		ft_strdel(&(p[j++]));
	ft_memdel((void **)&p);
	return (ret);
}

int			fexit(char **p)
{
	int		i;

	write_history(NULL);
	le_free(g_shell.line_e);
	tcsetattr(STDERR_FILENO, TCSADRAIN, g_shell.termiold);
	i = 0;
	if (p && p[0])
		i = get_exit_return_val(p);
	free_for_ft_built_in(g_shell.fptr);
	free_env(1);
	free_history();
	ft_free_tab(g_shell.aliasp);
	ast_free(&(g_shell.ast));
	free_jobs();
	exit(i);
	return (i);
}
