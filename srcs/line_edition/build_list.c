/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 04:46:11 by kicausse          #+#    #+#             */
/*   Updated: 2019/09/23 09:14:47 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_file	*build_completion_list_env(char *str,
		uint *list_size, t_edit *line_e)
{
	t_file	*list;
	int		start;

	*list_size = 0;
	if (!*str || !g_shell.envp || !*g_shell.envp || !g_shell.line_e->autocomp)
		return (NULL);
	list = NULL;
	start = 1;
	if (str[0] != '0' && str[1] == '{')
	{
		start = 2;
		++line_e->autocomp_point;
	}
	*list_size = search_similar_env_var(&list, str + start,
			ft_strlen(str + start));
	return (list);
}

void	call_list_func(t_edit *line_e, unsigned int comp_type, char *word)
{
	if (comp_type == 0)
	{
		line_e->autocomp_list = build_completion_list(word,
				ft_strlen(word), &line_e->autocomp_size);
	}
	else if (comp_type == 1)
	{
		line_e->autocomp_list = build_completion_list_files(word,
			ft_strlen(word), &line_e->autocomp_size);
	}
	else
	{
		line_e->autocomp_list = build_completion_list_env(word,
			&line_e->autocomp_size, line_e);
	}
}

int		build_list_from_word(t_edit *line_e)
{
	char			*word;
	unsigned int	comp_type;

	ft_file_list_delete(&line_e->autocomp_list);
	ft_bzero(&line_e->autocomp_list,
			(size_t)&line_e->autocomp_quote - (size_t)&line_e->autocomp_list);
	if ((word = get_autocompletion_word(line_e, &comp_type,
					&line_e->autocomp_point)) == NULL)
		return (0);
	if (word[0] == '/' || word[0] == '.')
		comp_type = 1;
	else if (word[0] == '$')
		comp_type = 2;
	line_e->autocomp = 1;
	call_list_func(line_e, comp_type, word);
	line_e->autocomp_list = merge_sort(line_e->autocomp_list);
	ft_strdel(&word);
	if (line_e->autocomp_list == NULL || line_e->autocomp == 0)
	{
		line_e->autocomp = 0;
		ft_file_list_delete(&line_e->autocomp_list);
	}
	return (line_e->autocomp_list == NULL ? 0 : 1);
}
