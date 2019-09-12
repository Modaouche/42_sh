/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 07:45:32 by araout            #+#    #+#             */
/*   Updated: 2019/07/18 07:47:27 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void		free_history(void)
{
	t_list		*head;
	t_list		*tmp;
	t_hnode		*n;

	head = g_shell.history->hist;
	while (head)
	{
		tmp = head;
		head = head->next;
		n = tmp->content;
		ft_strdel(&(n->cmd));
		free(n);
		free(tmp);
	}
	close(g_shell.history->fd);
	ft_memdel((void **)&(g_shell.history->path));
	ft_memdel((void **)&(g_shell.history));
}

void		init_history(void)
{
	char	*home_path;

	home_path = get_env_value("HOME");
	if (!home_path)
	{
		ft_putstr_fd("error : history need HOME env variable", 2);
		return ;
	}
	if (!(g_shell.history = (t_history *)ft_memalloc(sizeof(t_history))))
		return ;
	g_shell.history->path = ft_strjoin(home_path, "/.42sh_history");
	g_shell.history->fd = open(g_shell.history->path,\
			O_CREAT, S_IRUSR | S_IWUSR);
	g_shell.history->hist = build_hist_lst();
	g_shell.history->size = get_hist_size();
	ft_strdel(&home_path);
}

int			build_node(char *line, t_list **node)
{
	t_hnode		*content;

	if (line == NULL)
		return (-1);
	if (!(content = (t_hnode *)ft_memalloc(sizeof(t_hnode))))
		return (-1);
	content->cmd = ft_strdup(line);
	(*node)->content = content;
	(*node)->content_size = sizeof(content);
	return (1);
}

int			build_hist_lst_tool(t_list *head, t_list *node)
{
	char	*line;
	int		flag;

	flag = 0;
	while (get_next_line(g_shell.history->fd, &line) > 0)
	{
		flag = 1;
		if (!node && build_node(line, &head))
			node = head;
		else
		{
			if (!(node->next = (t_list *)ft_memalloc(sizeof(t_list))))
				return (-1);
			if (build_node(line, &node->next) == -1)
			{
				ft_strdel(&line);
				return (1);
			}
			node = node->next;
		}
		ft_strdel(&line);
	}
	return ((flag == 1) ? 1 : 0);
}

t_list		*build_hist_lst(void)
{
	t_list		*head;
	t_list		*node;

	node = NULL;
	if (!(head = (t_list *)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (!build_hist_lst_tool(head, node))
		ft_memdel((void **)&head);
	return (head);
}
