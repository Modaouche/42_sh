/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:42:00 by mgheraie          #+#    #+#             */
/*   Updated: 2019/06/17 03:42:48 by mgheraie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_test.h"

char		test_lnk(mode_t m)
{
	return ((S_ISLNK(m)) ? TRUE : FALSE);
}

char		test_sock(mode_t m)
{
	return ((S_ISSOCK(m)) ? TRUE : FALSE);
}

char		test_uid(mode_t m)
{
	return ((m | S_ISUID) ? TRUE : FALSE);
}

char		test_gid(mode_t m)
{
	return ((m | S_ISGID) ? TRUE : FALSE);
}

char		test_check_type_file(uint8_t flag, mode_t m)
{
	char		(*tabfct[9])(mode_t mode);

	tabfct[0] = test_blk;
	tabfct[1] = test_chr;
	tabfct[2] = test_dir;
	tabfct[3] = test_reg;
	tabfct[4] = test_gid;
	tabfct[5] = test_lnk;
	tabfct[6] = test_fifo;
	tabfct[7] = test_sock;
	tabfct[8] = test_uid;
	return (tabfct[flag - 2](m));
}
