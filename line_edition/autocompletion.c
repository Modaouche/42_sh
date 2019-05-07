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

void        print_autocompletion_list(t_list *list, int highlight)
{
    t_list          *tmp;
    int             i;
    unsigned int    max;
    unsigned int    maxcol;
    struct winsize  size;

    max = 0;
    tmp = list;
    while (tmp)
    {
        if (tmp->content_size > max)
            max = tmp->content_size;
        tmp = tmp->next;
    }
    ioctl(0, TIOCGWINSZ, &size);
    maxcol = size.ws_col / (max + 2);
    i = 0;
    while (list)
    {
        if (i == highlight)
        {
            tputs(tgetstr("mr", NULL), 1, ft_puti);
            print_with_pad(list->content, max + 2);
            tputs(tgetstr("me", NULL), 1, ft_puti);
        }
        else
            print_with_pad(list->content, max + 2);
        ++i;
        list = list->next;
        if (maxcol == 0 || i % maxcol == 0)
        {
            tputs(tgetstr("do", NULL), 1, ft_puti);
            tputs(tgetstr("cr", NULL), 1, ft_puti);    
        }
    }
}

unsigned int    search_similar_files(t_list **list, char *path, char *str, int len)
{
    DIR             *d;
    struct dirent   *f;
    unsigned int size;

    d = opendir(path);
    if (!d)
        return (0);
    size = 0;
    while ((f = readdir(d)) != NULL)
    {
        if (ft_strncmp(f->d_name, str, len) == 0)
        {
            char *tmp = ft_strdup(f->d_name);
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
    while (ft_strncmp(*env, "PATH=", 5) != 0)
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
    *list_size += search_similar_files(&list, ".", str, len);
    return (list);
}
