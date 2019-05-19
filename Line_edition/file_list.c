/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:03:29 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 01:48:52 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include "libft.h"

t_file		*ft_file_list_create(char *name)
{
	t_file *new;

	if ((new = ft_memalloc(sizeof(t_file))) == NULL)
		return (NULL);
	ft_printf("%s\n", name);
	new->name = ft_strdup(name);
	new->len = ft_strlen(name);
	return (new);
}


t_file		*ft_file_list_append(t_file **list, char *name)
{
	t_file *new;
	t_file *tmp;

	if (list == NULL)
		return (0);
	if ((new = ft_file_list_create(name)) == NULL)
		return (NULL);
	if (*list == NULL)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
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
