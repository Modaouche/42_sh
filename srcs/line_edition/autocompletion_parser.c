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
	return (c == ' ' || c == '\t' || c == '\n');
}

/*
**  quote_match
**
**  - Used during parsing when encountering a quote, it automatically skips
**  to the matching closing quote. Required to avoid parsing special
**  characters it may contain that could be considered as
**  a separator for example.
*/

void	quote_match(char *line, unsigned int *i, unsigned int maxlen, char c)
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
			return ;
	}
}

/*
**
**  parse_word
**
**  - Takes a part of a line and converts it into a single string.
**  It removes the quotes present in input while interpreting them.
**  Required for accurate autocompletion using quotes.
*/

char	*parse_word(char *line, unsigned int end)
{
	char			*str;
	unsigned int	i;
	unsigned int	x;
	unsigned int	escape;

	if ((str = ft_strnew(end)) == NULL)
		return (NULL);
	i = 0;
	x = 0;
	escape = 0;
	while (i < end && line[i])
	{
		if (escape == 1)
		{
			str[x++] = line[i++];
			escape = 0;
			continue ;
		}
		if (line[i] == '\\')
		{
			escape = 1;
			++i;
			continue ;
		}
		if (line[i] == '\'')
		{
			++i;
			while (i < end && line[i] != '\'' && line[i])
				str[x++] = line[i++];
			if (escape)
				str[x++] = '\\';
			if (i < end && line[i])
				++i;
			continue ;
		}
		if (line[i] == '"')
		{
			++i;
			escape = 0;
			while (i < end && line[i])
			{
				if (escape == 1)
				{
					if (ft_cfind(AUTOCOMP_ESCAPED_CHARS_IN_DBLQUOTE, line[i]) == -1)
						str[x++] = '\\';
					else
						str[x++] = line[i];
					escape = 0;
					++i;
					continue ;
				}
				if (line[i] == '"')
					break ;
				if (line[i] == '\\')
				{
					escape = 1;
					++i;
					continue ;
				}
				str[x++] = line[i++];
			}
			if (escape)
				str[x++] = '\\';
			if (i < end && line[i])
				++i;
			continue ;
		}
		str[x++] = line[i++];
	}
	return (str);
}

/*
**
**  get_last_slash
**
**  - Gets the position of the last / character.
**  Used when autocompleting a file path containing a /, to avoid
**  replacing the whole line and instead the last part of it.
*/

int		get_last_slash(char *line, unsigned int word_start,
		unsigned int word_end, t_edit *line_e)
{
	unsigned int i;
	unsigned int escape;

	while (word_end > word_start && line[word_end] != '/')
		--word_end;
	if (line[word_end] == '/')
		++word_end;
	i = word_start;
	escape = 0;
	line_e->autocomp_quote = 0;
	while (i < word_end)
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
			continue ;
		}
		if (line_e->line[i] == '"')
		{
			quote_match(line_e->line, &i, word_end, '"');
			line_e->autocomp_quote = 1;
			++i;
			continue ;
		}
		else if (line_e->line[i] == '\'')
		{
			quote_match(line_e->line, &i, word_end, '\'');
			line_e->autocomp_quote = 2;
			++i;
			continue ;
		}
		if (i >= word_end)
			break ;
		line_e->autocomp_quote = 0;
		++i;
	}
	return (word_end);
}

/*
**
**  get_autocompletion_word
**
**  - Finds the starting and ending point of the word at the current
**  cursor position, then calls parse_word to creates the string
**  containing the word and return it.
*/

char	*get_autocompletion_word(t_edit *line_e, unsigned int *argument,
		unsigned int *autocompletion_point)
{
	unsigned int i;
	unsigned int word_start;
	unsigned int word_end;
	unsigned int escape;
	unsigned int word_idx;

	i = 0;
	word_start = 0;
	word_end = 0;
	word_idx = 0;
	while (i < line_e->cursor_pos)
	{	
		word_start = i;
		word_end = i;
		line_e->autocomp_quote = 0;
		while (is_separator(line_e->line[i]) && i < line_e->cursor_pos)
			++i;
		if (i >= line_e->cursor_pos)
			break ;
		word_start = i;
		word_end = i;
		escape = 0;
		while (i < line_e->cursor_pos)
		{
			if (escape)
			{
				escape = 0;
				word_end = i++;
				continue ;
			}
			if (line_e->line[i] == '\\')
			{
				escape = 1;
				word_end = i++;
				continue ;
			}
			if (line_e->line[i] == '"')
			{
				quote_match(line_e->line, &i, line_e->cursor_pos, '"');
				word_end = i;
				line_e->autocomp_quote = 1;
			}
			else if (line_e->line[i] == '\'')
			{
				quote_match(line_e->line, &i, line_e->cursor_pos, '\'');
				word_end = i;
				line_e->autocomp_quote = 2;
			}
			if (is_separator(line_e->line[i]) || i >= line_e->cursor_pos)
				break ;
			word_end = i++;
			line_e->autocomp_quote = 0;
		}
		++word_idx;
	}
	*argument = word_idx > 1;
	if (word_idx == 0 && word_start == word_end)
		return (NULL);
	if (word_start == word_end && is_separator(line_e->line[word_start]))
	{
		*autocompletion_point = word_start + 1;
		*argument = 1;
		return (ft_strnew(0));
	}
	
	*autocompletion_point = get_last_slash(line_e->line, word_start, word_end + 1, line_e);
	return (parse_word(line_e->line + word_start, word_end - word_start + 1));
}
