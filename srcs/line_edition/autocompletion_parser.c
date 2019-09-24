/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion_parser.c                            :+:      :+:    :+:   */
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
**  autocompletion_parser.c
**
**  - A mini-parser, required to autocomplete input that uses quotes,
**  double quotes, escaping characters and spaces.
*/

/*
**	is_separator
**
**  - Determines whether the given character is an argument separator or not
*/

int		is_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == ';');
}

/*
**  get_last_slash
**
**  - Gets the position of the last / character.
**  Used when autocompleting a file path containing a /, to avoid
**  replacing the whole line and instead the last part of it.
*/

int		get_last_slash(t_edit *line_e, unsigned int word_start,
		unsigned int word_end)
{
	if (word_end > line_e->len)
		word_end = line_e->len;
	while (word_end > word_start && line_e->line[word_end] != '/')
		--word_end;
	if (line_e->line[word_end] == '/')
		++word_end;
	else if (line_e->autocomp_quote > 0)
		return (word_end + 1);
	else
		return (word_end);
	line_e->autocomp_quote = get_idx_quote_type(line_e->line, word_end);
	return (word_end);
}

int		detect_escaping_sequence(t_edit *line_e, unsigned int *escape,
		unsigned int *i, int *last_dollar)
{
	if (*escape)
	{
		*escape = 0;
		*i += 1;
		return (1);
	}
	if (line_e->line[*i] == '\\')
	{
		*escape = 1;
		*i += 1;
		*last_dollar = -1;
		return (1);
	}
	return (0);
}

int		get_last_dollar(t_edit *line_e, unsigned int word_start,
		unsigned int word_end)
{
	unsigned int	i;
	int				last_dollar;
	unsigned int	escape;

	i = word_start;
	last_dollar = -1;
	escape = 0;
	while (i < word_end)
	{
		if (detect_escaping_sequence(line_e, &escape, &i, &last_dollar))
			continue ;
		if (line_e->line[i] == '$')
			last_dollar = i;
		else if (!ft_isalnum(line_e->line[i]) && line_e->line[i] != '{')
			last_dollar = -1;
		++i;
	}
	if (last_dollar != -1
		&& (i = get_idx_quote_type(line_e->line, last_dollar)) != 2)
	{
		line_e->autocomp_point = last_dollar + 1;
		line_e->autocomp_quote = i;
		return (last_dollar);
	}
	return (word_start);
}
