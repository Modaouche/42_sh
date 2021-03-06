/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:50:49 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 08:48:05 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int			quote_parser(const char *line, char **word, unsigned int qt)
{
	if (qt == 2)
		qt = 0;
	if (!*word)
	{
		if (ft_strclen(line + qt, '\''))
			*word = ft_strcdup(line + qt, '\'');
	}
	else
	{
		if (ft_strclen(line + qt, '\''))
			*word = ft_strjoin_free(*word, ft_strcdup(line + qt, '\''), 3);
	}
	if (!ft_strchr(line + qt, '\''))
	{
		*word = (!*word) ? ft_strdup("\n") : ft_strjoin_free(*word, "\n", 1);
		return (0);
	}
	return (ft_strclen(line + qt, '\'') + 1);
}
