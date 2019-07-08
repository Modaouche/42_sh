/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 06:00:02 by araout            #+#    #+#             */
/*   Updated: 2019/07/08 08:19:05 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int			fexit(char **s)
{
	int		i;

	i = 0;
	(void)s;
	ft_strdel(&(g_shell.line_e->line));
	if (tcsetattr(STDERR_FILENO, TCSADRAIN, g_shell.termiold) == -1)
		toexit(0, "tcsetattr", 1);
	free_env();
	exit(0);
	return (0);
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

int			print_env(char **s)
{
	int		i;

	i = -1;
	(void)s;
	while (g_shell.envp[++i])
		ft_printf("%s\n", g_shell.envp[i]);
	return (1);
}

int			ft_clear(char **s)
{
	(void)s;
	tputs(tgetstr("cl", NULL), 1, ft_puti);
	return (1);
}

int			ft_pwd(char **s)
{
	char	*str;

	str = NULL;
	(void)s;
	str = getcwd(str, 1024);
	ft_printf("%s\n", str);
	ft_strdel(&str);
	return (1);
}
