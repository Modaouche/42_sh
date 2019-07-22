/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 07:17:53 by araout            #+#    #+#             */
/*   Updated: 2019/07/18 07:47:45 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

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
