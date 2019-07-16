/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:12:43 by araout            #+#    #+#             */
/*   Updated: 2019/07/16 02:37:53 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*double_bang(void)
{
	return (NULL);
}

void		write_history(char *line)
{
	int		fd;

	g_shell.history->line++;
	fd = open(g_shell.history->path, O_APPEND | O_RDWR);
	ft_putnbr_fd(g_shell.history->line, fd);
	write(fd, "\t", 1);
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

int			ft_history(void *ptr)
{
	t_list		*head;

	(void)ptr;
	head = g_shell.history->hist;
	while (head && head->content)
	{
		ft_printf("%d\t", ((t_hnode *)head->content)->index);
		ft_printf("%s\n", ((t_hnode*)head->content)->cmd);
		head = head->next;
	}
	return (1);
}
