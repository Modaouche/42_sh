/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 08:50:32 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/22 03:22:31 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_token *get_next_token(const char **line, unsigned int *i)
{
	t_token     *actual_token;

	if (!(actual_token = (t_token*)ft_memalloc(sizeof(t_token))))
		return (0);
	if (*line)
		skip_predicat(line, i, &ft_isspace_inhib);
	if (g_token_tab[(unsigned int)line[0][*i]])
		(*g_token_tab[(unsigned int)line[0][*i]])(actual_token, *line, i);
	return (actual_token);
}
