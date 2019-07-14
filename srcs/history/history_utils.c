/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 07:17:53 by araout            #+#    #+#             */
/*   Updated: 2019/07/15 01:22:39 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void		free_history(void)
{
	int		i;

	i = 0;
	while (g_shell.history->history && g_shell.history->history[i])
		ft_strdel(&(g_shell.history->history[i++]));
	ft_strdel(&(g_shell.history->path));
	ft_memdel((void *)&(g_shell.history->history));
	ft_memdel((void *)&(g_shell.history));
}

int			get_hist_line(void)
{
	unsigned int	i;

	i = 0;
	while (g_shell.history->history && g_shell.history->history[i])
		i++;
	return (i);
}

void		init_history(void)
{
	char	*home_path;

	home_path = get_env_value("HOME");
	if (!(g_shell.history = (t_history *)ft_memalloc(sizeof(t_history))))
		return ;
	g_shell.history->path = ft_strjoin(home_path, "/.42sh_history");
	g_shell.history->fd = open(g_shell.history->path,\
			O_CREAT, S_IRUSR | S_IWUSR);
	g_shell.history->offset_end = dump_history(&(g_shell.history->history));
	g_shell.history->line = get_hist_line();
	ft_strdel(&home_path);
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

int			dump_history(char ***ret)
{
	int				fd;
	char			*hist;
	char			buf[255];
	int				size;
	char			*tmp;

	size = 0;
	fd = dup(g_shell.history->fd);
	hist = NULL;
	ft_bzero(buf, 255);
	while (read(fd, buf, 255) > 0)
	{
		buf[254] = '\0';
		if (!hist)
			hist = ft_strdup(buf);
		else
		{
			tmp = hist;
			hist = ft_strjoin(hist, buf);
			free(tmp);
		}
	}
	*ret = ft_split(hist, "\n");
	free(hist);
	return (size);
}
