/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 04:46:11 by kicausse          #+#    #+#             */
/*   Updated: 2019/05/06 04:46:11 by kicausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	set_escape_str(t_parse_word *pw, char *line, unsigned int end)
{
	if (pw->escape)
		pw->str[pw->x++] = '\\';
	if (pw->i < end && line[pw->i])
		pw->i++;
}

void	match_quote_pw(t_parse_word *pw, char *line, unsigned int end)
{
	pw->i++;
	pw->escape = 0;
	while (pw->i < end && line[pw->i])
	{
		if (pw->escape == 1)
		{
			if (ft_cfind(AUTOCOMP_ESCAPED_CHARS_IN_DBLQUOTE,
				line[pw->i]) == -1)
				pw->str[pw->x++] = '\\';
			else
				pw->str[pw->x++] = line[pw->i];
			pw->escape = 0;
			pw->i++;
		}
		else if (line[pw->i] == '"')
			break ;
		else if (line[pw->i] == '\\')
		{
			pw->escape = 1;
			pw->i++;
		}
		else
			pw->str[pw->x++] = line[pw->i++];
	}
	set_escape_str(pw, line, end);
}

int		parse_word_match_check(t_parse_word *pw, char *line, unsigned int end)
{
	if (line[pw->i] == '\'')
	{
		++pw->i;
		while (pw->i < end && line[pw->i] != '\'' && line[pw->i])
			pw->str[pw->x++] = line[pw->i++];
		if (pw->escape)
			pw->str[pw->x++] = '\\';
		if (pw->i < end && line[pw->i])
			pw->i++;
		return (1);
	}
	else if (line[pw->i] == '"')
	{
		match_quote_pw(pw, line, end);
		return (1);
	}
	return (0);
}

/*
**  parse_word
**
**  - Takes a part of a line and converts it into a single string.
**  It removes the quotes present in input while interpreting them.
**  Required for accurate autocompletion using quotes.
*/

char	*parse_word(char *line, unsigned int end)
{
	t_parse_word	pw;

	if ((pw.str = ft_strnew(end)) == NULL)
		return (NULL);
	pw.i = 0;
	pw.x = 0;
	pw.escape = 0;
	while (pw.i < end && line[pw.i])
	{
		if (pw.escape == 1)
		{
			pw.str[pw.x++] = line[pw.i++];
			pw.escape = 0;
		}
		else if (line[pw.i] == '\\')
		{
			pw.escape = 1;
			++pw.i;
		}
		else if (!parse_word_match_check(&pw, line, end))
			pw.str[pw.x++] = line[pw.i++];
	}
	return (pw.str);
}
