/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_type_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 03:35:05 by mgheraie          #+#    #+#             */
/*   Updated: 2019/06/17 03:42:33 by mgheraie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_test.h"

char		test_blk(mode_t m)
{
	return ((S_ISBLK(m)) ? TRUE : FALSE);
}

char		test_chr(mode_t m)
{
	return ((S_ISCHR(m)) ? TRUE : FALSE);
}

char		test_dir(mode_t m)
{
	return ((S_ISDIR(m)) ? TRUE : FALSE);
}

char		test_reg(mode_t m)
{
	return ((S_ISREG(m)) ? TRUE : FALSE);
}

char		test_fifo(mode_t m)
{
	return ((S_ISFIFO(m)) ? TRUE : FALSE);
}
