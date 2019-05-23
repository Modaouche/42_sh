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

static char *dup_str_heredoc(t_edit *line_e)

{
	static	size_t backslash = 0;
	size_t	idx;
	char	*word;

        word = NULL;
	idx = ft_strlen(line_e->line) - 1;
	if (line_e->line[idx] != '\\')
	{
		word = (!backslash) ? ft_strdup(line_e->line)\
		       : ft_strjoin_free(word, ft_strdup(line_e->line), 3);
		backslash = 0;
		return (word);
	}
	while (line_e->line[idx] == '\\')
	{
        	word = (!backslash) ? ft_strndup(line_e->line, idx)\
		       : ft_strjoin_free(word, ft_strndup(line_e->line, idx) , 3);
		ft_printf("word = %s %d\n", word, idx);
    		init_line(line_e);
	        line_e->prompt_size = print_prompt(6);
            	line_edition(line_e);
            	if (!line_e->line)
                	line_e->line = ft_memalloc(1);
		idx = ft_strlen(line_e->line) - 1;
		backslash = 1;
	}
	return (word);
}

t_token *get_heredoc(t_edit *line_e)
{
	t_token     *actual_token;

	if (!(actual_token = (t_token*)ft_memalloc(sizeof(t_token))))
		return (0);
	actual_token->tokind = T_WORD;
	actual_token->lexeme = dup_str_heredoc(line_e);
	return (actual_token);
}
