/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 12:49:29 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 09:20:10 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				init_line(t_edit *line_e)
{
	if (!g_shell.line_e)
		g_shell.line_e = st_line();
	if (line_e->line)
		ft_strdel(&line_e->line);
	line_e->len_max = BUFFER_LEN;
	line_e->cursor_pos = 0;
	line_e->ofst = 0;
	line_e->len = 0;
	line_e->autocomp = 0;
	line_e->search_mode = 0;
	line_e->history_pos = 0;
}

t_edit				*st_line(void)
{
	static t_edit		line_e;

	return (&line_e);
}

t_ast_ptr			*st_ast(void)
{
	static t_ast_ptr	ast_head;

	return (&ast_head);
}
