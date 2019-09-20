/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 06:11:12 by araout            #+#    #+#             */
/*   Updated: 2019/08/30 11:49:23 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "built_in.h"

t_fptr			*init_fptr(void)
{
	t_fptr		*func;

	if (!(func = (t_fptr *)ft_memalloc(sizeof(t_fptr))))
		return (NULL);
	if (!(func->flag = ft_split(BUILTIN_LIST, " ")))
		return (NULL);
	func->f[0] = &ft_cd;
	func->f[1] = &print_env;
	func->f[2] = &ft_clear;
	func->f[3] = &ft_pwd;
	func->f[4] = &ft_setenv;
	func->f[5] = &ft_unsetenv_cmd;
	func->f[6] = &ft_history;
	func->f[7] = &ft_fc;
	func->f[8] = &ft_echo;
	func->f[9] = &type_main;
	func->f[10] = &ft_alias;
	func->f[11] = &ft_unalias;
	func->f[12] = &ft_test_main;
	func->f[13] = &fexit;
	func->f[14] = &ft_jobs;
	func->f[15] = &ft_fg;
	func->f[16] = &ft_bg;
	return (func);
}

void			free_for_ft_built_in(t_fptr *func)
{
	int		i;

	i = -1;
	while (func->flag && func->flag[++i])
		ft_strdel(&(func->flag[i]));
	ft_memdel((void **)&(func->flag));
	ft_memdel((void **)&func);
}

void			free_tmp(char **s)
{
	int		i;

	i = -1;
	while (s && s[++i])
		ft_strdel(s + i);
	ft_memdel((void *)&s);
}

/*
**	ft_built_in takes a segment of command like "cd /patati/patata"
**	and check if a built in has to be exetuted
**	return 1 a built_in has been executed
*/

int				ft_built_in(char *cmd)
{
	int			i;
	char		**args;

	if (cmd == NULL)
		return (0);
	i = 0;
	args = (char**)cmd;
	while (g_shell.fptr->f[i])
	{
		if (!(ft_strcmp(g_shell.fptr->flag[i], args[0])))
			return (g_shell.fptr->f[i](args));
		++i;
	}
	return (0);
}
