/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:48:28 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/23 09:43:32 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void    extend_quotes(t_edit *line_e, char **word, unsigned int *i)
{
	unsigned int offset;
	unsigned int ret;
	unsigned int qt;

	qt = 1;
	offset = *i;
	ret = 0;
	if (line_e->line[offset] == '\'')
		while (!(ret = quote_parser(line_e->line + offset, word, qt)))//pb du ret
		{
			qt = 2;
			offset = 0;
			init_line(line_e);
			g_shell.prompt_size = print_prompt(4);
			line_edition(line_e);
			if (!line_e->line)
				line_e->line = ft_memalloc(1);
		}
	else if (line_e->line[offset] == '\"')
		while (!(ret = word_parser(line_e->line + offset, word, qt)))//pb du ret
		{
			qt = 2;
			offset = 0;
			init_line(line_e);
			g_shell.prompt_size = print_prompt(5);
			line_edition(line_e);
			if (!line_e->line)
				line_e->line = ft_memalloc(1);
		}
	*i = offset + ret;
}

char    *get_word(unsigned int *i)
{
	char    *word;
	t_edit *line_e;
	int ret;

	line_e = st_line();
	word = NULL;
	while (!for_end_word_inhib(line_e->line[*i]))
	{
		if (ft_isquote_inhib(line_e->line[*i]))
			extend_quotes(line_e, &word, i);
		else
		{
			while (line_e->line[0] && !(ret = word_parser(line_e->line + *i, &word, 0)))
				if (!backslash_end(line_e, i, &ret))
					break ;
			*i += ret;
		}
	}
	return (word ? word : ft_strnew(0));
}
