/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:12:43 by araout            #+#    #+#             */
/*   Updated: 2019/07/16 05:33:51 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*double_bang(void)
{
	return (NULL);
}

void		write_history_tolist(char *line, t_list *head, t_hnode *n)
{
	char		*str;
	char		*tmp;

	if (!head || !head->content)
	{
		if (!(head = (t_list *)ft_memalloc(sizeof(t_list))))
			return ;
		tmp = ft_strjoin("0\t", line);
		build_node(tmp, &head);
		ft_strdel(&tmp);
		g_shell.history->hist = head;
		return ;
	}
	while (head && head->next)
		head = head->next;
	n = head->content;
	str = ft_itoa(n->index + 1);
	tmp = ft_strjoin(str, "\t");
	ft_strdel(&str);
	str = ft_strjoin(tmp, line);
	ft_strdel(&tmp);
	if (!(head->next = (t_list *)ft_memalloc(sizeof(t_list))))
		return ;
	build_node(str, &(head->next));
	ft_strdel(&str);
}

void		write_history(char *line)
{
	t_list		*head;
	t_hnode		*n;
	int			fd;

	fd = open(g_shell.history->path, O_RDWR);
	n = NULL;
	head = g_shell.history->hist;
	if (!line)
	{
		write(fd, 0, g_shell.history->size);
		lseek(fd, 0, SEEK_SET);
		while (head && head->content)
		{
			n = head->content;
			head = head->next;
			ft_printf("%s\n", n->cmd);
			ft_putnbr_fd(n->index, fd);
			ft_putstr_fd("\t", fd);
			ft_putstr_fd(n->cmd, fd);
			ft_putstr_fd("\n", fd);
		}
	}
	else
		write_history_tolist(line, head, n);
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
