/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_autocomp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 04:46:11 by kicausse          #+#    #+#             */
/*   Updated: 2019/09/23 09:14:47 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*escape_singlequote(char *name, unsigned int max)
{
	unsigned int	x;
	unsigned int	i;
	char			*new;

	i = 0;
	x = 0;
	while (name[i] && i < max)
		if (++x && name[i++] == '\'')
			x += 3;
	if ((new = ft_strnew(x)) == NULL)
		return (NULL);
	x = 0;
	while (*name && max-- != 0)
	{
		if (*name == '\'')
		{
			ft_memcpy(new + x, (char[]){0x27, 0x5c, 0x27, 0x27}, 4);
			x += 4;
		}
		else
			new[x++] = *name;
		++name;
	}
	return (new);
}

char	*escape_name(char *name, char *escaped_chars, unsigned int max)
{
	unsigned int	x;
	unsigned int	i;
	char			*new;

	i = 0;
	x = 0;
	while (name[i] && i < max)
	{
		if (ft_cfind(escaped_chars, name[i++]) != -1)
			++x;
		++x;
	}
	if ((new = ft_strnew(x)) == NULL)
		return (NULL);
	x = 0;
	i = 0;
	while (name[i] && i < max)
	{
		if (ft_cfind(escaped_chars, name[i]) != -1)
			new[x++] = '\\';
		new[x++] = name[i++];
	}
	return (new);
}
