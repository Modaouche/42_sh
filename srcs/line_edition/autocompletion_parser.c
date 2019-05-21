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

int		is_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

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
	while (i < end)
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
		str[x++] = line[i++];
	}
	return (str);
}

int		get_last_slash(char *line, unsigned int word_start,
		unsigned int word_end)
{
	while (word_end > word_start && line[word_end] != '/')
		--word_end;
	return (word_end + 1);
}

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
			}
			else if (line_e->line[i] == '\'')
			{
				quote_match(line_e->line, &i, line_e->cursor_pos, '\'');
				word_end = i;
			}
			if (is_separator(line_e->line[i]))
				break ;
			word_end = i++;
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
	*autocompletion_point = get_last_slash(line_e->line, word_start, word_end + 1);
	return (parse_word(line_e->line + word_start, word_end + 1));
}
