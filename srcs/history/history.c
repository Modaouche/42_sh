/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:12:43 by araout            #+#    #+#             */
/*   Updated: 2019/07/23 22:57:41 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*double_bang(void)
{
	t_list		*h;

	h = g_shell.history->hist;
	while (h->next)
		h = h->next;
	return (((t_hnode *)h->content)->cmd);
}

void		del_hist(void)
{
	int		fd;

	if (!(fd = open(g_shell.history->path, O_TRUNC | O_CREAT | O_WRONLY, 600)))
		return ;
	close(fd);
	free_history();
	init_history();
}

void		write_history_tolist(char *line, t_list *head)
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
		if (!(fd = open(g_shell.history->path, O_RDWR)))
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
		write_history_tolist(line, head);
}

int			ft_history(void *ptr)
{
	t_list		*head;
	int			i;
	char		**p;

	i = 1;
	p = ptr;
	head = g_shell.history->hist;
	if (ptr && !ft_strcmp(p[1], "-c"))
		del_hist();
	else
	{
		while (head && head->content)
		{
			ft_putnbr(i);
			write(1, "\t", 1);
			ft_printf("%s\n", ((t_hnode*)head->content)->cmd);
			head = head->next;
			i++;
		}
	}
	return (1);
}
