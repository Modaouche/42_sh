/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:03:29 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 01:48:52 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		start_autocomp(t_edit *line_e, char *prevkey)
{
	if (line_e->autocomp != 0 && prevkey[0] == '\t' && prevkey[1] == '\0'
			&& line_e->autocomp_list != NULL)
	{
		line_e->autocomp = 2;
		replace_word_from_completion(line_e);
		print_comp_list(line_e, line_e->autocomp_idx);
		return ;
	}
	if (build_list_from_word(line_e) == 0 || line_e->autocomp_size == 1)
	{
		if (line_e->line == NULL)
			return ;
		replace_word_from_completion(line_e);
		cancel_autocompletion(line_e);
		return ;
	}
	replace_word(line_e, line_e->autocomp_list->name,
			get_last_common_char(line_e->autocomp_list), NULL);
	line_e->autocomp = 1;
	print_comp_list(line_e, -1);
}

void		cancel_autocompletion(t_edit *line_e)
{
	line_e->autocomp = 0;
	line_e->search_mode = 0;
	cursor_after(line_e);
	tputs(tgetstr("cd", NULL), 1, ft_puti);
	tputs(tgetstr("up", NULL), 1, ft_puti);
	cursor_move_from_to(line_e, line_e->len, line_e->cursor_pos);
	ft_file_list_delete(&line_e->autocomp_list);
}
