/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 02:17:36 by kicausse          #+#    #+#             */
/*   Updated: 2019/08/30 12:25:27 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "built_in.h"

void	print_alias_list(void)
{
	int i;

	if (g_shell.aliasp == NULL)
		return ;
	i = 0;
	while (g_shell.aliasp[i])
	{
		if (g_shell.aliasp[i] != '\0')
			ft_putendl(g_shell.aliasp[i]);
		++i;
	}
}

int		print_alias(char *alias, int *errcode)
{
	char *value;

	if ((value = get_alias_value(alias)) == NULL)
	{
		*errcode = 1;
		return (1);
	}
	ft_printf("%s=%s\n", alias, value);
	return (0);
}

void	set_alias(char *alias, int *errcode)
{
	unsigned int separator;

	separator = ft_cfind(alias, '=');
	alias[separator] = '\0';
	if (str_match_charset("\\\"'();&$|<> \t\n\r\v`", alias))
	{
		ft_printf("alias: %s: invalid alias name\n", alias);
		*errcode = 1;
	}
	else
		set_alias_value(alias, &alias[separator + 1]);
	alias[separator] = '=';
}

int		ft_alias(void *str)
{
	char **args;
	int i;
	int errcode;

	errcode = 0;
	if (!(args = str) || !args[0] || !args[1])
	{
		print_alias_list();
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (ft_cfind(args[i], '=') == -1)
			print_alias(args[i], &errcode);
		else
			set_alias(args[i], &errcode);
		++i;
	}
	return (errcode);
}

int		ft_unalias(void *str)
{
	char **args;
	int i;
	int errcode;

	errcode = 0;
	if (!(args = str) || !args[0] || !args[1])
	{
		print_alias_list();
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (remove_alias(args[i]) == 0)
		{
			ft_printf("unalias: no such element: %s\n", args[i]);
			errcode = 1;
		}
		++i;
	}
	return (errcode);
}
