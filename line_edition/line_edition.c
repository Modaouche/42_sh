/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:03:29 by modaouch          #+#    #+#             */
/*   Updated: 2019/04/25 19:19:49 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int         str_add(t_edit *line_e, const char to_add)
{
    char    *new;

    if (!line_e->line)
    {
        if (!(line_e->line = ft_strnew(BUFFER_LEN)))
            return (0);
        line_e->line[0] = to_add;
        return (1);
    }
    if (ft_strlen(line_e->line) >= line_e->len_max)
    {
        line_e->len_max += BUFFER_LEN;
        if (!(new = ft_strnew(line_e->len_max)))
            return (0);
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
        if (line_e->line && key[2] == S_KEY_ARW_LEFT && line_e->cursor_pos > 0)
        {
            line_e->cursor_pos -= 1;
            tputs(tgetstr("le", NULL), 1, ft_puti);
        }
        else if (line_e->line && key[2] == S_KEY_ARW_RIGHT && line_e->cursor_pos < ft_strlen(line_e->line))
        {
            struct winsize size;
            ioctl(0, TIOCGWINSZ, &size);
            line_e->cursor_pos += 1;
            if ((line_e->cursor_pos + 25) % size.ws_col == 0)
            {
                tputs(tgetstr("do", NULL), 1, ft_puti);
                tputs(tgetstr("cr", NULL), 1, ft_puti);
            }
            else
                tputs(tgetstr("nd", NULL), 1, ft_puti);
        }
        else if (key[2] == S_KEY_ARW_UP)
           ft_putstr_fd("              KEY top\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", STDERR_FILENO);
        else if (key[2] == S_KEY_ARW_DOWN)
           ft_putstr_fd("              KEY bot\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", STDERR_FILENO);
        return ;
    }
    if (line_e->cursor_pos && line_e->line && (key[0] == S_KEY_ARW_RET && !key[1]))
    {
        line_e->cursor_pos -= 1;
        if (line_e->line[0])
        {
            ft_memmove(line_e->line + (line_e->cursor_pos),\
                    line_e->line + (line_e->cursor_pos + 1),\
                    ft_strlen(line_e->line + (line_e->cursor_pos + 1)));
        }
        line_e->line[ft_strlen(line_e->line) - 1] = '\0';
        tputs(tgetstr("le", NULL), 1, ft_puti);
        write(STDERR_FILENO, " ", 1);
        tputs(tgetstr("le", NULL), 1, ft_puti);
        ft_putstr_fd(line_e->line + line_e->cursor_pos, STDERR_FILENO);
        ft_putchar_fd(' ', STDERR_FILENO);
        cursor_reposition(ft_strlen(line_e->line + line_e->cursor_pos) + 1);
    }
    // ft_putstr("key too long comming soon - ");
}//in tabptrfct

int     line_edition(t_edit *line_e)
{
    int ret;
    char key[MAX_KEY_LEN];

    if (tcsetattr(STDERR_FILENO, TCSADRAIN, line_e->termios) == -1)
		toexit(0, "tcsetattr");
    while ("Line edition loop")
    {
	   ft_bzero(key, MAX_KEY_LEN);
	   ret = read(STDIN_FILENO, key, MAX_KEY_LEN);
        if (ret == -1 || ret == 0)
            perror("ret chelou :");
        if (key[0] == S_KEY_RET && !key[1])
        {
            if (tcsetattr(STDERR_FILENO, TCSADRAIN, line_e->termiold) == -1)
	           toexit(0, "tcsetattr");//maybe just turn off termcap instead of exit
            return (1);
        }    
        putkey_in_line(line_e, key);
        // ft_printf("[%s]", line_e->line);//printf a revoir si il est clean , revoir sur le github de nico
    }
    return (0);
}
