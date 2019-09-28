/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 06:00:02 by araout            #+#    #+#             */
/*   Updated: 2019/09/23 12:43:44 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int			fexit(char **p)
{
	int		i;
	int		j;

	j = 0;
	write_history(NULL);
	le_free(g_shell.line_e);
	tcsetattr(STDERR_FILENO, TCSADRAIN, g_shell.termiold);
	i = 0;
	if (p && p[0])
	{
		i = p[1] ? ft_atoi(p[1]) : 0;
		if (p[1] && !ft_strisdigit(p[1]) && (i = 1))
			ft_printf_fd(2, "exit: numeric argument required\n");
		while (p[j])
			ft_strdel(&(p[j++]));
	}
	ft_memdel((void **)&p);
	free_for_ft_built_in(g_shell.fptr);
	free_env(1);
	free_history();
	ft_free_tab(g_shell.aliasp);
	ast_free(&(g_shell.ast));
	free_jobs();
	exit(i);
	return (i);
}

void		cd_set_env(int exec_flag, char *pwd)
{
	char	*tmp;

	tmp = NULL;
	if (exec_flag == 1)
	{
		g_shell.envp = set_var_env("OLDPWD", pwd, g_shell.envp);
		ft_strdel(&pwd);
		pwd = getcwd(tmp, 1024);
		g_shell.envp = set_var_env("PWD", pwd, g_shell.envp);
	}
	ft_strdel(&pwd);
}

int			print_env(char **args)
{
	int		i;

	(void)args;
	i = -1;
	while (g_shell.intern_var && g_shell.intern_var[++i])
		ft_printf("%s\n", g_shell.intern_var[i]);
	i = -1;
	while (g_shell.envp[++i])
		ft_printf("%s\n", g_shell.envp[i]);
	return (0);
}

int			ft_clear(char **ptr)
{
	(void)ptr;
	tputs(tgetstr("cl", NULL), 1, ft_puti);
	return (0);
}

int			ft_pwd(char **ptr)
{
	char	*str;

	str = NULL;
	(void)ptr;
	str = getcwd(str, 1024);
	ft_printf("%s\n", str);
	ft_strdel(&str);
	return (0);
}
