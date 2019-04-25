/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 11:52:28 by modaouch          #+#    #+#             */
/*   Updated: 2019/04/04 13:36:05 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void		init_line(t_edit *line_e)
{
	if (line_e->line)
		ft_strdel(&line_e->line);
	line_e->len_max = BUFFER_LEN;
	line_e->cursor_pos = 0;
	line_e->i = 0;
}
