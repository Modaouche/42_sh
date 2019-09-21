/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 01:12:56 by mgheraie          #+#    #+#             */
/*   Updated: 2019/09/22 01:49:59 by mgheraie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "tild.h"
#include <pwd.h>
/*
char	*get_env(void)
{
	char	**env;
	int		last;

	env = g_shell.envp;
	while (env && *env)
	{
		if (ft_strncmp(*env, "HOME=", 5) == 0)
		{
			if ((last = ft_strgetlastocc(*env + 5, '/')) == -1)
				return (NULL);
			return (ft_strsub(*env, 5, last + 1));
		}
		env++;
	}
	return (NULL);
}

char	*get_home(void)
{
	char	**env;

	env = g_shell.envp;
	while (env && *env)
	{
		if (ft_strncmp(*env, "HOME=", 5) == 0)
			return (ft_strdup(*env + 5));
		++env;
	}
	return (NULL);
}
*/
char	*tild(char *s)
{
	char			*tmp;
	struct passwd	*passwd;

	ft_printf("RECEIVED [%s]\n", s);
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) == 1)
		return ((getpwnam(getlogin()))->pw_dir);
	tmp = s;
	if (!(passwd = getpwnam(tmp)))
		return (NULL);
	if (!(tmp = ft_strdup(passwd->pw_dir)))
		return (NULL);
	return (tmp);
}
