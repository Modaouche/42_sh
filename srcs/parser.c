/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <kicausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:16:46 by kicausse          #+#    #+#             */
/*   Updated: 2019/03/02 11:08:05 by kicausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	match_quote(char *str, int i, char quote)
{
	int escape;

	escape = 0;
	while (str[i])
	{
		if (escape == 1)
		{
			escape = 0;
			if (str[i])
				++i;
			continue ;
		}
		if (quote == '"' && str[i] == '\\')
			escape = 1;
		if (str[i] == quote)	
			return (i + 1);
		++i;
	}
	return (-1);
}

int count_actions(char *str)
{
	int count;
	int i;
	int escape;

	count = 0;
	i = 0;
	while (i >= 0 && str[i])
	{
		while (str[i] == ' ')
			++i;
		escape = 0;
		while (i >= 0 && str[i])
		{
			if (escape == 1)
			{
				escape = 0;
				if (str[i])
					++i;
				continue ;
			}
			if (str[i] == '\\')
				escape = 1;
			if (str[i] == ' ')
				break ;
			if (str[i] == '"')
			{
				i = match_quote(str, i + 1, '"');
				continue ;
			}
			if (str[i] == '\'')
			{
				i = match_quote(str, i + 1, '\'');
				continue ;
			}
			++i;
		}
		++count;
	}
	if (i == -1)
		ft_printf_fd(2, "\nUnclosed quote, please get back to line edition\n");
	return (count);
}

int parse_tab(char *str, char **tab)
{
	int count;
	int i;
	int escape;
	int start;

	count = 0;
	i = 0;
	while (i >= 0 && str[i])
	{
		while (str[i] == ' ')
			++i;
		escape = 0;
		start = i;
		while (i >= 0 && str[i])
		{
			if (escape == 1)
			{
				escape = 0;
				if (str[i])
					++i;
				continue ;
			}
			if (str[i] == '\\')
				escape = 1;
			if (str[i] == ' ')
				break ;
			if (str[i] == '"')
			{
				ft_strcpy(str + i, str + i + 1);
				i = match_quote(str, i, '"');
				if (i == -1)
				{
					ft_printf_fd(2, "\nUnclosed quote\n");
					return (0);
				}
				--i;
				ft_strcpy(str + i, str + i + 1);
				continue ;
			}
			if (str[i] == '\'')
			{
				ft_strcpy(str + i, str + i + 1);
				i = match_quote(str, i, '\'');
				if (i == -1)
				{
					ft_printf_fd(2, "\nUnclosed quote\n");
					return (0);
				}
				--i;
				ft_strcpy(str + i, str + i + 1);
				continue ;
			}
			++i;
		}
		if ((tab[count] = ft_strsub(str, start, i)) == NULL)
			return (0);
		++count;
	}
	tab[count] = 0;
	return (1);
}

int		parser(char *line) /* Generates a two dimensionnal array containing each written argument, taking into account single and double quotes */
{
	int		count;
	char	**tab;

	if (line == 0)
	{
		ft_printf_fd(2, "\nParser returned NULL string\n");
		return (0);
	}
	count = count_actions(line);
	ft_printf("\nCount is %d\n", count);
	tab = (char**)ft_memalloc(sizeof(char*) * (count + 1));
	parse_tab(line, tab);
	for(int i = 0; tab[i]; ++i)
	{
		ft_printf("[%s]\n", tab[i]);
		free(tab[i]);
	}
	free(tab);
	return (0);
}
