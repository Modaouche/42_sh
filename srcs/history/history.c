/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:12:43 by araout            #+#    #+#             */
/*   Updated: 2019/07/18 03:02:39 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*double_bang(void)
{
	return (NULL);
}

void		write_history_tolist(char *line, t_list *head, t_hnode *n)
{
	if (!head || !head->content)
	{
		if (!(head = (t_list *)ft_memalloc(sizeof(t_list))))
			return ;
		build_node(line, &head);
		g_shell.history->hist = head;
		return ;
	}
	while (head && head->next)
		head = head->next;
	n = head->content;
	if (!(head->next = (t_list *)ft_memalloc(sizeof(t_list))))
		return ;
	build_node(line, &(head->next));
}

void		write_history(char *line)
{
	t_list		*head;
	t_hnode		*n;
	int			fd;

	n = NULL;
	head = g_shell.history->hist;
	if (!line)
	{
		if (!(fd = open(g_shell.history->path, O_RDWR | O_APPEND)))
		{
			ft_putstr_fd("cannot open", 2);
			return ;
		}
		while (head && head->content)
		{
			n = head->content;
			head = head->next;
			ft_putendl_fd(n->cmd, fd);
		}
		close(fd);
	}
	else
		write_history_tolist(line, head, n);
}

int			ft_history(void *ptr)
{
	t_list		*head;
	int			i;

	(void)ptr;
	i = 1;
	head = g_shell.history->hist;
	while (head && head->content)
	{
		ft_putnbr(i);
		write(1, "\t", 1);
		ft_printf("%s\n", ((t_hnode*)head->content)->cmd);
		head = head->next;
		i++;
	}
	return (1);
}
