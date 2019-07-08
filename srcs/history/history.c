/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:12:43 by araout            #+#    #+#             */
/*   Updated: 2019/07/07 22:27:26 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		init_history(void)
{
	g_shell.hist_path = ft_strjoin(getenv("HOME"), "/.42sh_history");
}

/*
** write each cmd in $HOME/.42sh_history
*/
void		write_history(char *line)
{
	int		fd;

	fd = open(g_shell.hist_path, O_APPEND | O_RDWR);
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

char		**dump_history(void)
{
	int				fd;
	char			*hist;
	char			buf[255];
	char			**ret;

	fd = open(g_shell.hist_path, O_RDONLY);
	hist = NULL;
	ft_bzero(buf, 255);
	while (read(fd, buf, 255) > 0)
	{
		buf[254] = '\0';
		if (!hist)
			hist = ft_strdup(buf);
		else
		{
			ret = &hist;
			hist = ft_strjoin(hist, buf);
			ft_strdel(ret);
		}
	}
	ret = ft_split(hist, "\n");
	free(hist);
	return (ret);
}
