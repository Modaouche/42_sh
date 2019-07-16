/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 07:17:53 by araout            #+#    #+#             */
/*   Updated: 2019/07/16 05:30:14 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void		free_history(void)
{
	t_list		*head;
	t_list		*tmp;
	t_hnode		*n;

	write_history(NULL);
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
}

int			build_node(char *line, t_list **node)
{
	t_hnode		*content;
	int			i;

	if (line == NULL)
		return (-1);
	i = 0;
	if (!(content = (t_hnode *)ft_memalloc(sizeof(t_hnode))))
		return (-1);
	content->index = ft_atoi(line);
	while (line && line[i] && *node)
	{
		if (line[i] == '\t' && line[i + 1])
		{
			content->cmd = ft_strdup(line + i + 1);
			(*node)->content = content;
			(*node)->content_size = sizeof(content);
			return (1);
		}
		i++;
	}
	free(content);
	return (-1);
}

t_list		*build_hist_lst(void)
{
	t_list		*head;
	t_list		*node;
	char		*line;

	node = NULL;
	if (!(head = (t_list *)ft_memalloc(sizeof(t_list))))
		return (NULL);
	while (get_next_line(g_shell.history->fd, &line) > 0)
	{
		if (!node && build_node(line, &head))
			node = head;
		else
		{
			if (!(node->next = (t_list *)ft_memalloc(sizeof(t_list))))
				return (NULL);
			if (build_node(line, &node->next) == -1)
			{
				ft_strdel(&line);
				return (head);
			}
			node = node->next;
		}
		ft_strdel(&line);
	}
	return (head);
}

off_t		get_hist_size(void)
{
	struct stat	s;
	int			size;

	stat(g_shell.history->path, &s);
	size = s.st_size;
	return (size);
}

void		init_history(void)
{
	char	*home_path;

	home_path = get_env_value("HOME");
	if (!(g_shell.history = (t_history *)ft_memalloc(sizeof(t_history))))
		return ;
	if (!home_path)
	{
		ft_putstr_fd("error : history need HOME env variable", 2);
		return ;
	}
	g_shell.history->path = ft_strjoin(home_path, "/.42sh_history");
	g_shell.history->fd = open(g_shell.history->path,\
			O_CREAT, S_IRUSR | S_IWUSR);
	g_shell.history->hist = build_hist_lst();
	g_shell.history->size = get_hist_size();
	ft_strdel(&home_path);
}
