/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_merge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 00:19:54 by kicausse          #+#    #+#             */
/*   Updated: 2019/09/25 00:19:58 by kicausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_file		*merge(t_file *a, t_file *b, t_file *head)
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

t_file		*merge_sort(t_file *p)
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
