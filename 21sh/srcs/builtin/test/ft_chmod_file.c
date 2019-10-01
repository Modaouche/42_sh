/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chmod_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:55:50 by mgheraie          #+#    #+#             */
/*   Updated: 2019/06/17 03:42:06 by mgheraie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_test.h"

char		test_grpx(mode_t mode)
{
	return ((S_IXGRP | mode) ? TRUE : FALSE);
}

char		test_usrr(mode_t mode)
{
	return ((S_IRUSR | mode) ? TRUE : FALSE);
}

char		test_usrw(mode_t mode)
{
	return ((S_IWUSR | mode) ? TRUE : FALSE);
}

char		test_usrx(mode_t mode)
{
	return ((S_IXUSR | mode) ? TRUE : FALSE);
}

char		test_check_chmod_file(struct stat buf, uint8_t flag)
{
	char	(*tabfct[9])(mode_t m);

	tabfct[0] = test_usrr;
	tabfct[1] = test_usrw;
	tabfct[2] = test_usrx;
	tabfct[3] = test_othr;
	tabfct[4] = test_othw;
	tabfct[5] = test_othx;
	tabfct[6] = test_grpr;
	tabfct[7] = test_grpw;
	tabfct[8] = test_grpx;
	if (getuid() == buf.st_uid)
		return (tabfct[flag - 11](buf.st_mode));
	if (getgid() == buf.st_gid)
		return (tabfct[flag - 5](buf.st_mode));
	return (tabfct[flag - 8](buf.st_mode));
}
