/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 02:11:29 by araout            #+#    #+#             */
/*   Updated: 2019/08/28 03:41:21 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int		get_index_fc_by_string(char *arg)
{
	int		i;
	t_list	*head;
	int		index;

	index = -1;
	i = 1;
	head = g_shell.history->hist;
	if (!arg)
		return (get_hist_nbline());
	while ((head = head->next) != NULL)
	{
		i++;
		if (!ft_strncmp(((t_hnode *)head->content)->cmd, arg, ft_strlen(arg)))
			index = i;
	}
	if (index == get_hist_nbline() + 1)
		index--;
	return (index);
}

char	*get_line_to_exec(int index)
{
	t_list	*head;
	int		i;

	i = 1;
	head = g_shell.history->hist;
	if (i == index)
		return (((t_hnode *)head->content)->cmd);
	while (head->next)
	{
		if (i == index)
			return (((t_hnode *)head->content)->cmd);
		i++;
		head = head->next;
	}
	return (((t_hnode *)head->content)->cmd);
}

int		exec_fc_s(char **args, char *line, int index)
{
	int		i;

	i = get_argument_starting_index(args, 's');
	if (i == -1)
		index = get_hist_nbline() + 1;
	else if (ft_isdigit(*(args[i])) || *(args[i]) == '-' || *(args[i]) == '+')
	{
		index = ft_atoi(args[i]);
		set_a_b_under_zero(&index, &index);
	}
	else
	{
		index = get_index_fc_by_string(args[i]);
		if (index == -1)
		{
			ft_putstr_fd("42sh: fc: no command found\n", 2);
			return (-1);
		}
	}
	line = ft_strdup(get_line_to_exec(index));
	init_line(g_shell.line_e);
	g_shell.line_e->line = line;
	line_parser(g_shell.line_e);
	line_execution();
	return (1);
}
