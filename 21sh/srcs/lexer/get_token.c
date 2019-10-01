/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 08:58:16 by araout            #+#    #+#             */
/*   Updated: 2019/09/23 08:58:33 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_token		*get_next_token(char **line, unsigned int *i)
{
	t_token		*actual_token;

	if (!(actual_token = (t_token*)ft_memalloc(sizeof(t_token))))
		return (0);
	if (*line)
		skip_predicat(line, i, &ft_isspace_inhib);
	if (g_token_tab[(unsigned int)line[0][*i]])
		(*g_token_tab[(unsigned int)line[0][*i]])(actual_token, *line, i);
	return (actual_token);
}
