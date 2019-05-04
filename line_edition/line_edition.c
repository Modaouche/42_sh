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
#include "libft.h"
#include <dirent.h>

int         str_add(t_edit *line_e, const char to_add)
{
    char    *new;

    if (!line_e->line)
    {
        if (!(line_e->line = ft_strnew(BUFFER_LEN)))
            return (0);
        line_e->line[0] = to_add;
        line_e->len = 1;
        return (1);
    }
    if (line_e->len >= line_e->len_max)
    {
        line_e->len_max += BUFFER_LEN;
        if (!(new = ft_strnew(line_e->len_max)))
            return (0);
        ft_memcpy(new, line_e->line, line_e->len);
        ft_strdel(&(line_e->line));
        line_e->line = new;
    }
    if (!(new = (char *)ft_memalloc(line_e->len_max)))
        return (0);
    ft_memcpy(new, line_e->line, line_e->cursor_pos);
    new[line_e->cursor_pos] = to_add;
    ft_memcpy(new + (line_e->cursor_pos + 1), line_e->line\
        + line_e->cursor_pos, line_e->len - line_e->cursor_pos);
    ft_strdel(&(line_e->line));
    line_e->line = new;
    line_e->len += 1;
    return (1);
}

void    print_with_pad(char *str, int maxlen)
{
    unsigned int   i;
    int            len;

    len = ft_strlen(str);
    write(0, str, len);
    i = maxlen - len;
    while (i > 0)
    {
        write(0, " ", 1);
        --i;
    }
}

void    search_similar_files(t_list **list, char *path, char *str, int len)
{
    DIR             *d;
    struct dirent   *f;

    d = opendir(path);
    if (!d)
        return ;
    while ((f = readdir(d)) != NULL)
    {
        if (ft_strncmp(f->d_name, str, len) == 0)
        {
            char *tmp = ft_strdup(f->d_name);
            if (tmp)
                ft_list_append(list, tmp, ft_strlen(f->d_name));
        }
    }
}

t_list  *build_completion_list(char *str, int len, char **env)
{
    t_list *list;

    list = NULL;
    if (env == NULL)
        return (NULL);
    while (ft_strncmp(*env, "PATH=", 5) != 0)
        ++env;
    if (*env == NULL)
        return (NULL);
    char *path = *env + 5;
    while (*path != 0)
    {
        int i = 0;
        while (path[i] != ':' && path[i] != '\0')
            ++i;
        if (path[i] == ':')
        {
            path[i] = '\0';
            search_similar_files(&list, path, str, len);
            path[i] = ':';
            ++i;
        }
        else
            search_similar_files(&list, path, str, len);
        path += i;
    }
    (void)str;
    (void)len;
    return (list);
}

void		putkey_in_line(t_edit *line_e, char *prevkey, char *key)
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
        if (line_e->cursor_pos <= line_e->len)
            line_e->cursor_pos += 1;
        write(STDERR_FILENO, key, 1);
        ft_putstr_fd(line_e->line + line_e->cursor_pos, STDERR_FILENO);
        cursor_reposition(line_e->len - line_e->cursor_pos);
        return ;
    }
    else if (ft_strlen(key) <= 1 && key[0] == '\t')
    {
        if (line_e->line == NULL)
            return ;
        if (prevkey[0] == '\t' && ft_strlen(prevkey) <= 1 && line_e->autocompletion_list != NULL)
        {
            //autocompletion arrow mode
            return ;
        }
        unsigned int str_start;
        str_start = line_e->cursor_pos;
        while (str_start > 0 && line_e->line[str_start] != ' ')
            --str_start;
        if (str_start == line_e->cursor_pos)
            return ;
        ft_list_delete(&line_e->autocompletion_list);
        line_e->autocompletion_list = build_completion_list(line_e->line + str_start, line_e->cursor_pos - str_start, line_e->env);
        unsigned int i = 0;
        if (line_e->autocompletion_list == NULL)
            return ;
        line_e->autocompletion = 1;
        tputs(tgetstr("sc", NULL), 1, ft_puti);
        //autocomplete
        //cursor positionning
        tputs(tgetstr("do", NULL), 1, ft_puti);
        tputs(tgetstr("cr", NULL), 1, ft_puti);
        unsigned int max = 0;
        t_list *tmp = line_e->autocompletion_list;
        while (tmp)
        {
            if (tmp->content_size > max)
                max = tmp->content_size;
            tmp = tmp->next;
        }
        struct winsize size;
        ioctl(0, TIOCGWINSZ, &size);
        int maxcol = size.ws_col / (max + 2);
        i = 0;
        tmp = line_e->autocompletion_list;
        while (tmp)
        {
            print_with_pad(tmp->content, max + 2);
            ++i;
            tmp = tmp->next;
            if (i % maxcol == 0)
            {
                tputs(tgetstr("do", NULL), 1, ft_puti);
                tputs(tgetstr("cr", NULL), 1, ft_puti);    
            }
        }
        //restore cursor pos
        tputs(tgetstr("rc", NULL), 1, ft_puti);
    }
    else if (is_arrow(key))
    {
        if (line_e->line && key[2] == S_KEY_ARW_LEFT && line_e->cursor_pos > 0)
        {
            struct winsize size;
            ioctl(0, TIOCGWINSZ, &size);
            line_e->cursor_pos -= 1;
            if (line_e->line[line_e->cursor_pos] == '\n'
                || (line_e->cursor_pos + line_e->prompt_size + 1) % size.ws_col == 0)
            {
                tputs(tgetstr("up", NULL), 1, ft_puti);
                unsigned int i = 0;
                while (line_e->cursor_pos - i != 0)
                {
                    if(line_e->line[line_e->cursor_pos - i] == '\n')
                        break ;
                    ++i;
                }
                while ((i-- + line_e->prompt_size) > 0)
                    tputs(tgetstr("nd", NULL), 1, ft_puti);
            }
            else
                tputs(tgetstr("le", NULL), 1, ft_puti); 
        }
        else if (line_e->line && key[2] == S_KEY_ARW_RIGHT && line_e->cursor_pos < line_e->len)
        {
            struct winsize size;
            ioctl(0, TIOCGWINSZ, &size);
            line_e->cursor_pos += 1;
            if (line_e->line[line_e->cursor_pos] == '\n'
                || (line_e->cursor_pos + line_e->prompt_size) % size.ws_col == 0)
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
    else if (line_e->cursor_pos && line_e->line && (key[0] == S_KEY_ERASE && !key[1]))
    {
        line_e->cursor_pos -= 1;
        line_e->len -= 1;
        if (line_e->line[0])
        {
            ft_memmove(line_e->line + (line_e->cursor_pos),\
                    line_e->line + (line_e->cursor_pos + 1),\
                    line_e->len - line_e->cursor_pos);
        }
        line_e->line[line_e->len] = '\0';
        tputs(tgetstr("le", NULL), 1, ft_puti);
        write(STDERR_FILENO, " ", 1);
        tputs(tgetstr("le", NULL), 1, ft_puti);
        ft_putstr_fd(line_e->line + line_e->cursor_pos, STDERR_FILENO);
        ft_putchar_fd(' ', STDERR_FILENO);
        cursor_reposition(line_e->len - line_e->cursor_pos + 1);
    }
    // ft_putstr("key too long comming soon - ");
}//in tabptrfct

int     line_edition(t_edit *line_e)
{
    int ret;
    char key[MAX_KEY_LEN];
    char prevkey[MAX_KEY_LEN];

    line_e->prompt_size = 26;
    line_e->autocompletion = 0;
    if (tcsetattr(STDERR_FILENO, TCSADRAIN, line_e->termios) == -1)
		toexit(0, "tcsetattr");
    ft_bzero(prevkey, MAX_KEY_LEN);
    while (1)
    {
	   ft_bzero(key, MAX_KEY_LEN);
	   ret = read(STDIN_FILENO, key, MAX_KEY_LEN);
        if (ret == -1 || ret == 0)
            perror("ret chelou :");
        if (key[0] == S_KEY_ENTER && !key[1])
        {
            if (tcsetattr(STDERR_FILENO, TCSADRAIN, line_e->termiold) == -1)
               toexit(0, "tcsetattr");//maybe just turn off termcap instead of exit
            break ;
        }
        putkey_in_line(line_e, prevkey, key);
        ft_memcpy(prevkey, key, MAX_KEY_LEN);
        // ft_printf("[%s]", line_e->line);//printf a revoir si il est clean , revoir sur le github de nico
    }
    return (1);
}
