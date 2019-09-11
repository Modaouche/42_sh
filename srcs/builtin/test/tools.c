/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:54:25 by mgheraie          #+#    #+#             */
/*   Updated: 2019/06/16 05:50:42 by mgheraie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_test.h"

char		*test_get_pathname(char *s)
{
	char	*tmp;
	int		i;
	int		save;

	i = -1;
	save = 0;
	while (s[++i])
	{
		if (s[i] == '/')
			save = i;
	}
	if (!(tmp = ft_strnew(save)))
		return (NULL);
	i = 0;
	while (i < save)
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

char		*test_get_filename(char *s, char *buf)
{
	int		save;

	save = ft_strgetlastocc(s, '/');
	return (ft_strncpy(buf, s, save));
}

DIR			*test_opendir(char *s)
{
	int		save;
	char	*path;
	DIR		*dir;

	if ((ft_strchri(s, '/')) == -1)
		return (opendir("."));
	save = ft_strgetlastocc(s, '/');
	if (!(path = ft_strsub(s, 0, save)))
		return (NULL);
	if (!(dir = opendir(path)))
		return (NULL);
	ft_strdel(&path);
	return (dir);
}

char		test_get_stat(char *path, char *name,
		struct stat *tmp, DIR *dir)
{
	struct dirent	*rep;
	struct stat		buf;

	buf = *tmp;
	while ((rep = readdir(dir)))
		if (!(ft_strcmp(rep->d_name, name)))
			break ;
	if ((stat(path, &buf)))
		if ((lstat(path, &buf)))
			return (FALSE);
	*tmp = buf;
	return (TRUE);
}

size_t		ft_dstrlen(char **s)
{
	int i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

int			ft_strgetlastocc(char *s, char c)
{
	int i;
	int save;

	save = -1;
	i = -1;
	while (s[i])
	{
		if (s[i] == c)
			save = i;
		i++;
	}
	return (save);
}

int			ft_strchri(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] == c)
		return (i);
	return (-1);
}
