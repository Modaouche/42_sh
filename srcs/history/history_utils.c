/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 07:17:53 by araout            #+#    #+#             */
/*   Updated: 2019/07/31 05:14:11 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

char		*get_hist_line_from_end(int position)
{
	t_list	*head;
	int		size;

	size = get_hist_nbline() + 1;
	head = g_shell.history->hist;
	while (head && size > position)
	{
		head = head->next;
		--size;
	}
	if (size != position || head == NULL)
		return (NULL);
	return (((t_hnode*)head->content)->cmd);
}

int			get_hist_nbline(void)
{
	t_list		*head;
	int			i;

	i = 0;
	head = g_shell.history->hist;
	while (head && (head = head->next))
		i++;
	return (i);
}

off_t		get_hist_size(void)
{
	struct stat	s;
	int			size;

	stat(g_shell.history->path, &s);
	size = s.st_size;
	return (size);
}
