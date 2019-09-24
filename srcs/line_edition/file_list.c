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

char		*ft_strdup_printable(char *name)
{
	unsigned int	x;
	unsigned int	i;
	char			*new;

	i = 0;
	x = 0;
	while (name[i])
	{
		if (ft_isprint(name[i++]))
			++x;
	}
	if ((new = ft_strnew(x)) == NULL)
		return (NULL);
	i = 0;
	x = 0;
	while (name[i])
	{
		if (ft_isprint(name[i]))
			new[x++] = name[i];
		++i;
	}
	return (new);
}

/*
**  List functions made specifically for the autocompletion linked list
**  Nothing particularly interesting happens here.
*/

t_file		*ft_file_list_create(char *name, int type)
{
	t_file *new;

	if ((new = ft_memalloc(sizeof(t_file))) == NULL)
		return (NULL);
	if ((new->name = ft_strdup_printable(name)) == NULL)
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

	if (*name == '\0')
		return (NULL);
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
