/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:12:43 by araout            #+#    #+#             */
/*   Updated: 2019/07/12 04:15:28 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*double_bang(void)
{
	char	**hist;
	int		i;
	int		j;
	char	*ret;

	j = 0;
	i = -1;
	ret = NULL;
	hist = NULL;
	if (!(dump_history(&hist)))
		return (NULL);
	while (hist[i])
		i++;
	while (hist[i - 1][j])
	{
		if ((hist[i][j] == '\t') && (ret = ft_strdup(&(hist[i][j + 1]))))
			break ;
		j++;
	}
	i = -1;
	while (hist[++i])
		ft_strdel(&(hist[i]));
	ft_memdel((void **)hist);
	return (ret);
}

int			ft_history(void *ptr)
{
	int		fd;
	char	*line;

	(void)ptr;
	fd = dup(g_shell.history->fd);
	lseek(fd, 0, SEEK_SET);
	while (get_next_line(fd, &line) > 0)
	{
		ft_printf("%s\n", line);
		ft_strdel(&line);
	}
	close(fd);
	return (1);
}
