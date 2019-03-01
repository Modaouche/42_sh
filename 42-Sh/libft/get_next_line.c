/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 15:58:03 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/17 19:43:02 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_line(char *s_line[], char **line, int i, const int fd)
{
	char		*to_free;
	int			bt;

	bt = i ? 1 : 0;
	i = 0;
	while (s_line[fd][i + 1] && s_line[fd][i] != '\n')
		i++;
	if (s_line[fd][i] == '\n' && bt == 1)
	{
		to_free = s_line[fd];
		*line = ft_strcdup(s_line[fd], '\n');
		s_line[fd] = ft_strdup(&s_line[fd][i + 1]);
		free(to_free);
		return (1);
	}
	if (bt == 0)
		*line = ft_strcdup(s_line[fd], '\n');
	if ((s_line[fd][i] || i) && bt == 0)
	{
		to_free = s_line[fd];
		s_line[fd] = ft_strdup(&s_line[fd][i + 1]);
		free(to_free);
		return (1);
	}
	return (0);
}

static int		ft_util(const int fd, char *s_line[], const int ret, char *buff)
{
	char		*to_free;

	if (ret == -1)
	{
		if (!buff)
			free(buff);
		return (1);
	}
	buff[ret] = '\0';
	to_free = s_line[fd];
	s_line[fd] = ft_strjoin(to_free, buff);
	if (!to_free)
		free(to_free);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char	*s_line[OPEN_MAX];
	char		*buff;
	int			ret;

	if (read(fd, "", 0) == -1 || fd > OPEN_MAX || !line)
		return (-1);
	if (!s_line[fd])
	{
		if (!(s_line[fd] = ft_strnew(GNL_BUFF + 1)))
			return (-1);
		if ((ret = read(fd, s_line[fd], GNL_BUFF)))
			s_line[fd][ret] = '\0';
	}
	if (!(buff = ft_strnew(GNL_BUFF + 1)))
		return (-1);
	while ((ret = read(fd, buff, GNL_BUFF)) && ft_util(fd, s_line, ret, buff))
		if ((ft_line(s_line, line, 1, fd)) == 1)
			return (ft_util(0, 0, -1, buff));
	if ((ft_line(s_line, line, 0, fd)) == 1)
		return (ft_util(0, 0, -1, buff));
	free(buff);
	!s_line[fd] ? free(s_line[fd]) : 0;
	return (0);
}
