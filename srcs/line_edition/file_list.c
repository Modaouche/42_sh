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

	if (list == NULL)
		return (0);
	if ((new = ft_file_list_create(name, type)) == NULL)
		return (NULL);
	if (*list == NULL)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next != NULL && ft_strcmp(name, tmp->next->name) >= 0)
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
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
