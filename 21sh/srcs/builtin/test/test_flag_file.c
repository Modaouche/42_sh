/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_flag_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 05:39:36 by mgheraie          #+#    #+#             */
/*   Updated: 2019/09/21 00:30:34 by mgheraie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_test.h"

static char			test_dispatch_file(uint16_t flag, struct stat buf)
{
	if (flag == TEST_E)
		return (TRUE);
	if (flag == TEST_S)
		return ((buf.st_size == 0) ? TRUE : FALSE);
	if (flag <= TEST_U)
		return (test_check_type_file(flag, buf.st_mode));
	return (test_check_chmod_file(buf, flag));
}

char				test_flag_file(uint16_t flag, void *s)
{
	DIR				*dir;
	struct stat		buf;
	char			name[1024];
	char			res;

	if (!s)
		return (TRUE);
	if (!(dir = test_opendir((char*)s)))
		return (1);
	ft_strncpy(name, s, ft_strgetlastocc(s, '/'));
	test_get_filename(s, name);
	res = test_get_stat(s, name, &buf, dir);
	(res == TRUE) ? res = (test_dispatch_file(flag, buf)) : 0;
	closedir(dir);
	return (res);
}
