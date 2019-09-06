/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 02:28:12 by kicausse          #+#    #+#             */
/*   Updated: 2019/09/04 02:28:12 by kicausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "built_in.h"

char	*get_alias_value(char *name)
{
	unsigned int tmp;
	char 	**array;

	if ((array = g_shell.aliasp) == NULL)
		return (NULL);
	while (*array)
	{
		tmp = ft_strlcmp(*array, name);
		if (tmp != 0 && (*array)[tmp] == '=')
			return (*array + tmp + 1);
		++array;
	}
	return (0);
}


int		remove_alias(char *name)
{
	unsigned int tmp;
	unsigned int i;

	i = 0;
	while (g_shell.aliasp[i])
	{
		tmp = ft_strlcmp(g_shell.aliasp[i], name);
		if (tmp != 0 && (g_shell.aliasp[i])[tmp] == '=')
		{
			g_shell.aliasp[i][0] = '\0';
			return (1);
		}
		++i;
	}
	return (0);
}

char	**copy_alias_tab(char **array, char *newelem)
{
	int				len;
	int				i;
	char			**output;

	i = -1;
	len = (newelem != NULL);
	while (array && array[++i])
		if (array[i][0] != '\0')
			len++;
	if ((output = ft_memalloc(sizeof(char**) * (len + 1))) == NULL)
		return (NULL);
	i = 0;
	len = 0;
	while (array && array[i])
	{
		if (array[i][0] != '\0'
			&& (output[len++] = ft_strdup(array[i])) == NULL)
			return (reverse_free_tab(output, len));
		++i;
	}
	if (newelem != 0)
		output[len++] = newelem;
	output[len] = NULL;
	return (output);
}

void	set_alias_value(char *name, char *value)
{
	unsigned int	tmp;
	unsigned int	i;
	char			**tmptab;

	if (g_shell.aliasp == NULL)
	{
		g_shell.aliasp = copy_alias_tab(NULL, concat_alias_string(name, value));
		return ;
	}
	i = 0;
	while (g_shell.aliasp[i])
	{
		tmp = ft_strlcmp(g_shell.aliasp[i], name);
		if (tmp != 0 && (g_shell.aliasp[i])[tmp] == '=')
		{
			ft_strdel(&(g_shell.aliasp[i]));
			g_shell.aliasp[i] = concat_alias_string(name, value);
			return ;
		}
		++i;
	}
	tmptab = g_shell.aliasp;
	g_shell.aliasp = copy_alias_tab(tmptab, concat_alias_string(name, value));
	ft_free_tab(tmptab);
}


char	*concat_alias_string(char *name, char *value)
{
	unsigned int	len;
	char			*output;

	len = ft_strlen(name);
	if ((output = ft_strnew(len + 1 + ft_strlen(value))) == NULL)
		return (NULL);
	ft_memcpy(output, name, len);
	output[len] = '=';
	ft_strcpy(output + len + 1, value);
	return (output);
}
