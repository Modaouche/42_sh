/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <kicausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:03:29 by kicausse          #+#    #+#             */
/*   Updated: 2019/05/14 01:48:52 by kicausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

/*
**  List functions made specifically for the autocompletion linked list
**  Nothing particularly interesting happens here.
*/

t_file		*ft_file_list_create(char *name, int type)
{
	t_file *new;

	if ((new = ft_memalloc(sizeof(t_file))) == NULL)
		return (NULL);
	if ((new->name = ft_strdup(name)) == NULL)
	{
		free(new);
		return (NULL);
	}
	new->len = ft_strlen(new->name);
	new->type = type;
	return (new);
}


t_file		*ft_file_list_append(t_file **list, char *name, int type)
{
	t_file *new;

	if (list == NULL || (new = ft_file_list_create(name, type)) == NULL)
		return (NULL);
	new->next = *list;
	*list = new;
	return (new);
}

void		ft_file_list_delete(t_file **list)
{
	t_file *tmp;

	if (list == NULL)
		return ;
	while (*list != NULL)
	{
		tmp = *list;
		*list = (*list)->next;
		ft_strdel(&tmp->name);;
		free(tmp);
	} 
}

t_file		*ft_file_list_at(t_file *list, unsigned int idx)
{
	while (list != NULL)
	{
		if (idx-- == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}

void    ft_list_sort(t_file **begin_list)
{
        t_file  *curr;
        t_file	tmp;

        if (begin_list == 0 || (curr = *begin_list) == 0)
                return ;
        while (curr->next != 0)
        {
                while (ft_strcmp(curr->name, curr->next->name) > 0)
                {
                        tmp.name = curr->name;
                        curr->name = curr->next->name;
                        curr->next->name = tmp.name;
                        tmp.len = curr->len;
                        curr->len = curr->next->len;
                        curr->next->len = tmp.len;
                        tmp.type = curr->type;
                        curr->type = curr->next->type;
                        curr->next->type = tmp.type;
                        curr = *begin_list;
                }
                curr = curr->next;
        }
}
