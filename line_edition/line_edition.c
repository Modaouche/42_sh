/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:03:29 by modaouch          #+#    #+#             */
/*   Updated: 2019/03/02 11:02:00 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int         str_add(t_edit *line_e, const char to_add)
{
    char    *new;

    if (!line_e->line)
    {
        line_e->line = (char *)ft_memcpy(ft_memalloc(BUFFER_LEN + 1), &to_add, 1);
        return (1);
    }
    if (ft_strlen(line_e->line) >= line_e->len_max)
    {
        line_e->len_max += BUFFER_LEN;
        new = (char *)ft_memalloc(line_e->len_max);
        ft_memcpy(new, line_e->line, ft_strlen(line_e->line));
        ft_strdel(&(line_e->line));
        line_e->line = new;
    }
    if (!(new = (char *)ft_memalloc(line_e->len_max)))
        return (0);
    ft_memcpy(new, line_e->line, line_e->cursor_pos);
    new[line_e->cursor_pos] = to_add;
    ft_memcpy(new + (line_e->cursor_pos + 1), line_e->line\
        + line_e->cursor_pos, ft_strlen(line_e->line + line_e->cursor_pos));
    ft_strdel(&(line_e->line));
    line_e->line = new;
    return (1);
}

void		putkey_in_line(t_edit *line_e, char *key)
{
    if (!key)
    {
        ft_putendl_fd("error : key :null", STDERR_FILENO);
        return ;
    }
    if (ft_strlen(key) <= 1 && ft_isprint(key[0]))
    {
        if (!(str_add(line_e, *key)))
            toexit(line_e, "malloc");
        if (line_e->cursor_pos <= ft_strlen(line_e->line))
            line_e->cursor_pos += 1;
        write(STDERR_FILENO, key, 1);
        ft_putstr_fd(line_e->line + line_e->cursor_pos, STDERR_FILENO);
        cursor_reposition(ft_strlen(line_e->line + line_e->cursor_pos));
        return ;
    }
    if (is_arrow(key))
    {
        if (line_e->line && key[2] == 68 && line_e->cursor_pos > 0)
        {
            line_e->cursor_pos -= 1;
            tputs(tgetstr("le", NULL), 1, ft_puti);
        }
        if (line_e->line && key[2] == 67 && line_e->cursor_pos < ft_strlen(line_e->line))
        {
            line_e->cursor_pos += 1;
            tputs(tgetstr("nd", NULL), 1, ft_puti);
        }
        if (key[2] == 65)
           ft_putstr_fd("KEY top ", STDERR_FILENO);
        if (key[2] == 66)
           ft_putstr_fd("KEY bot ", STDERR_FILENO);
        return ;
    }
    if (line_e->cursor_pos && line_e->line && (key[0] == 127 && !key[1]))
    {
        line_e->cursor_pos -= 1;
        if (line_e->line[0])
            ft_memmove(line_e->line + (line_e->cursor_pos),\
            line_e->line + (line_e->cursor_pos + 1),\
            ft_strlen(line_e->line + (line_e->cursor_pos + 1)));
        ft_bzero(line_e->line + ft_strlen(line_e->line) - 1, 1);
        tputs(tgetstr("le", NULL), 1, ft_puti);
        write(STDERR_FILENO, " ", 1);
        tputs(tgetstr("le", NULL), 1, ft_puti);
        ft_putstr_fd(line_e->line + line_e->cursor_pos, STDERR_FILENO);
        ft_putchar_fd(' ', STDERR_FILENO);
        cursor_reposition(ft_strlen(line_e->line + line_e->cursor_pos) + 1);
    }
    //ft_putstr("unknow key or no managed");
}//in tabptr de fct

int     line_edition(t_edit *line_e)
{
    int ret;
    char key[MAX_KEY_LEN];

    while ("Line edition")
    {
		ft_bzero(key, MAX_KEY_LEN + 1);
		ret = read(STDIN_FILENO, key, MAX_KEY_LEN);
        if (ret == -1 || ret == 0)
            perror("ret chelou :");
        if (key[0] == 10 && !key[1])
            return (1) ;
        putkey_in_line(line_e, key);
        //ft_printf("[%s] ", line_e->line);
    }
    return (0);
}