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
	t_file *tmp;

	tmp = *list;
	while (tmp != NULL)
	{
		if (ft_strcmp(name, tmp->name) == 0)
			return (NULL);
		tmp = tmp->next;
	}
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
		ft_strdel(&tmp->name);
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

t_file			*merge(t_file *a, t_file *b, t_file *head)
{
	t_file	**r;

	r = &head;
	if (a && b)
	{
		while (1)
		{
			if (ft_strcmp(a->name, b->name) <= 0 && (*r = a))
			{
				r = &a->next;
				a = a->next;
				if (!a)
					break ;
			}
			else if ((*r = b) || 1)
			{
				r = &b->next;
				b = b->next;
				if (!b)
					break ;
			}
		}
	}
	*r = (a == NULL) ? b : a;
	return (head);
}

t_file			*merge_sort(t_file *p)
{
	t_file	*a;
	t_file	*b;
	t_file	*last;

	b = p;
	a = b;
	last = NULL;
	while (a && a->next)
	{
		last = b;
		b = b->next;
		a = a->next->next;
	}
	if (last == NULL)
		return (p);
	last->next = NULL;
	return (merge(merge_sort(p), merge_sort(b), NULL));
}
