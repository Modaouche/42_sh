/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 04:46:11 by kicausse          #+#    #+#             */
/*   Updated: 2019/05/06 04:46:11 by kicausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

/*
**  quote_match
**
**  - Used during parsing when encountering a quote, it automatically skips
**  to the matching closing quote. Required to avoid parsing special
**  characters it may contain that could be considered as
**  a separator for example.
*/

int		quote_match(char *line, unsigned int *i, unsigned int maxlen, char c)
{
	unsigned int escape;

	escape = 0;
	while (++(*i) < maxlen)
	{
		if (escape == 1)
		{
			escape = 0;
			continue ;
		}
		if (line[*i] == '\\' && c == '"')
		{
			escape = 1;
			continue ;
		}
		if (line[*i] == c)
			break ;
	}
	return (c == '"' ? 1 : 2);
}


int		get_idx_quote_type(char *line, unsigned int idx)
{
	unsigned int i;
	unsigned int quote;
	unsigned int escape;

	i = 0;
	quote = 0;
	escape = 0;
	while (i < idx && line[i])
	{
		if (escape)
		{
			escape = 0;
			++i;
			continue ;
		}
		if (line[i] == '\\')
		{
			escape = 1;
			++i;
			quote = 0;
			continue ;
		}
		if (line[i] == '"')
		{
			quote = quote_match(line, &i, idx, '"');
			++i;
			continue ;
		}
		else if (line[i] == '\'')
		{
			quote = quote_match(line, &i, idx, '\'');
			++i;
			continue ;
		}
		if (i++ >= idx)
			break ;
		quote = 0;
	}
	return (quote);
}
