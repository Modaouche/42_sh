/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 17:38:23 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/22 17:25:49 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void    token_isword(t_token *actual_token, const char *line, unsigned int *i)
{
	char *word;
	unsigned int i2;

	i2 = *i;
	skip_predicat(&line, &i2, &ft_isdigit);
	if (line[i2] == '<' || line[i2] == '>')
		token_isio_nb(actual_token, line, i);
	else
	{
		word = get_word(i);
		actual_token->tokind = T_WORD;
		actual_token->lexeme = word;
	}
}

void    token_isio_nb(t_token *actual_token, const char *line, unsigned int *i)
{
	unsigned int len;

	len = *i;
	skip_predicat(&line, &len, &ft_isdigit);
	actual_token->tokind = T_IO_NB;
	actual_token->lexeme = ft_strndup(line + *i, len - *i);
	skip_predicat(&line, i, &ft_isdigit);
}
