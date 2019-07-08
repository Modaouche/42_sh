/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 01:30:43 by araout            #+#    #+#             */
/*   Updated: 2019/07/08 04:14:26 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static t_fptr	*init_fptr(void)
{
	t_fptr		*func;

	if (!(func = (t_fptr *)ft_memalloc(sizeof(t_fptr))))
		return (NULL);
	if (!(func->flag = (char **)ft_memalloc(sizeof(char *) * 5)))
		return (NULL);
	func->flag[0] = ft_strdup("cd");
	func->flag[1] = ft_strdup("env");
	func->flag[2] = ft_strdup("clear");
	func->flag[3] = NULL;
	func->f[0] = &ft_cd;
	func->f[1] = &print_env;
	func->f[2] = &ft_clear;
	func->f[3] = NULL;
	return (func);
}

int				ft_clear(char **s)
{
	(void)s;
	tputs(tgetstr("cl", NULL), 1, ft_puti);
	return (1);
}

static void		free_for_ft_built_in(t_fptr *func, char **tmp)
{
	int		i;

	i = -1;
	while (func->flag[++i])
		ft_strdel(&(func->flag[i]));
	ft_memdel((void **)&(func->flag));
	ft_memdel((void **)&func);
	i = 0;
	while (tmp[i])
		ft_strdel(&tmp[i++]);
	ft_memdel((void **)&tmp);
	
}

/*
**	ft_built_in takes a segment of command like "cd /patati/patata" 
**	and check if a built in has to be exetuted 
** works for cd , env , exit , clear
*/

static void		check_exit(char **tmp, int i)
{
	if (!ft_strcmp(tmp[0], "exit"))
	{
		while (tmp[i])
			ft_strdel(&(tmp[i++]));
		fexit(NULL);
	}
}

int				ft_built_in(char *cmd)
{
	t_fptr		*func;
	int			i;
	char		**tmp;

	i = 0;
	if (!(tmp = ft_split(cmd, " ")))
		return (-1);
	check_exit(tmp, i);
	if ((func = init_fptr()) == NULL)
		return (0);
	while (func->f[i])
	{
		if (!(ft_strcmp(func->flag[i], tmp[0])))
		{
			func->f[i](tmp);
			free_for_ft_built_in(func, tmp);
			return (1);
		}
		i++;
	}
	free_for_ft_built_in(func, tmp);
	return (0);
}
