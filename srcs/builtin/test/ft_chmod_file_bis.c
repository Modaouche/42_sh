/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chmod_file_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 03:37:31 by mgheraie          #+#    #+#             */
/*   Updated: 2019/06/17 03:42:18 by mgheraie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_test.h"

char		test_othr(mode_t mode)
{
	return ((S_IROTH | mode) ? TRUE : FALSE);
}

char		test_othw(mode_t mode)
{
	return ((S_IWOTH | mode) ? TRUE : FALSE);
}

char		test_othx(mode_t mode)
{
	return ((S_IXOTH | mode) ? TRUE : FALSE);
}

char		test_grpr(mode_t mode)
{
	return ((S_IRGRP | mode) ? TRUE : FALSE);
}

char		test_grpw(mode_t mode)
{
	return ((S_IWGRP | mode) ? TRUE : FALSE);
}
