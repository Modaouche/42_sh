/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 12:49:29 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 02:22:35 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void		init_line(t_edit *line_e)
{
	if (line_e->line)
		ft_strdel(&line_e->line);
	line_e->len_max = BUFFER_LEN;
	line_e->cursor_pos = 0;
	line_e->ofst = 0;
	line_e->len = 0;
}
