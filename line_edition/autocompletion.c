/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 04:46:11 by kicausse          #+#    #+#             */
/*   Updated: 2019/05/06 04:46:11 by kicausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include "libft.h"
#include <dirent.h>

int     get_last_common_char(t_list *list)
{
    int     last;
    char    c;
    t_list  *tmp;

    if (list == NULL || list->content == NULL)
        return (1);
    last = 1;
    while (list->content[last] != '\0')
    {
        tmp = list;
        c = list->content[last];
        while (tmp != NULL)
        {
            if (tmp->content == NULL || tmp->content[last] != c)
                return (last);
            tmp = tmp->next;
        }
        ++last;
    }
    return (last);  
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

int         get_list_longest_word(t_list *list)
{
    unsigned int    longest;

    longest = 0;
    while (list)
    {
        if (list->content_size > longest)
            longest = list->content_size;
        list = list->next;
    }
    return (longest + 2);
}

void        print_autocompletion_list(t_edit *line_e, int highlight)
{
    t_list          *list;
    int             i;
    int             newlines;
    unsigned int    maxcol;
    unsigned int    max;
    struct winsize  size;

    cursor_after(line_e);
    tputs(tgetstr("cd", NULL), 1, ft_puti);
    list = line_e->autocompletion_list;
    max = get_list_longest_word(list);
    ioctl(0, TIOCGWINSZ, &size);
    maxcol = size.ws_col / max;
    line_e->autocompletion_maxcol = maxcol;
    i = 0;
    newlines = 0;
    while (list)
    {
        if (i++ == highlight)
            tputs(tgetstr("mr", NULL), 1, ft_puti);
        print_with_pad(list->content, max);
        tputs(tgetstr("me", NULL), 1, ft_puti);
        list = list->next;
        if ((maxcol == 0 || i % maxcol == 0) && list != NULL)
        {
            ++newlines;
            tputs(tgetstr("do", NULL), 1, ft_puti);
            tputs(tgetstr("cr", NULL), 1, ft_puti);    
        }
    }
    while (newlines-- >= 0)
        tputs(tgetstr("up", NULL), 1, ft_puti);
    cursor_actualpos(line_e);
}

unsigned int    search_similar_files(t_list **list, char *path, char *str, int len)
{
    DIR             *d;
    struct dirent   *f;
    unsigned int    size;
    char            *tmp;

    if (!(d = opendir(path)))
        return (0);
    size = 0;
    while ((f = readdir(d)) != NULL)
    {
        if (ft_strncmp(f->d_name, str, len) == 0)
        {
            tmp = ft_strdup(f->d_name);
            if (tmp && ft_list_append(list, tmp, ft_strlen(f->d_name)))
                ++size;
        }
    }
    return (size);
}

t_list  *build_completion_list(char *str, int len, char **env, unsigned int *list_size)
{
    t_list  *list;
    char    *path;
    int     i;

    list = NULL;
    if (env == NULL)
        return (NULL);
    while (*env != NULL && ft_strncmp(*env, "PATH=", 5) != 0)
        ++env;
    if (*env == NULL)
        return (NULL);
    path = *env + 5;
    *list_size = 0;
    while (*path != 0)
    {
        i = 0;
        while (path[i] != ':' && path[i] != '\0')
            ++i;
        if (path[i] == ':')
        {
            path[i] = '\0';
            *list_size += search_similar_files(&list, path, str, len);
            path[i] = ':';
            ++i;
        }
        else
            *list_size += search_similar_files(&list, path, str, len);
        path += i;
    }
    return (list);
}
