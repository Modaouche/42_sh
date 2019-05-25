/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 08:50:32 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/22 03:22:31 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static char *dup_str_heredoc(t_edit *line_e)
{
	size_t	backslash;
	ssize_t	idx;
	char	*word;

	word = NULL;
	backslash = false;
	((idx = ft_strlen(line_e->line) - 1) == -1) ? idx++ : 0;
	if (line_e->line[idx] != '\\')
		return (ft_strdup(line_e->line));
	backslash = true;
	word = ft_strndup(line_e->line, idx);
	while (backslash == true)
	{
		init_line(line_e);
		line_e->prompt_size = print_prompt(6);
		line_edition(line_e);
		(!line_e->line) ? line_e->line = ft_strnew(1) : 0;
		if ((idx = ft_strlen(line_e->line) - 1) == -1 || line_e->line[idx] != '\\')
		{
			backslash = false;
			idx++;
		}
		word = ft_strjoin_free(word, ft_strndup(line_e->line, idx) , 3);
	}
	return (word);
}

t_token *get_heredoc(t_edit *line_e, int *begin)
{
	t_token     *actual_token;

	*begin = 0;
	if (!(actual_token = (t_token*)ft_memalloc(sizeof(t_token))))
		return (0);
	actual_token->tokind = T_WORD;
	actual_token->lexeme = dup_str_heredoc(line_e);
	return (actual_token);
}
