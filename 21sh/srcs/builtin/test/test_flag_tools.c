/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_flag_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 05:38:30 by mgheraie          #+#    #+#             */
/*   Updated: 2019/06/16 05:50:59 by mgheraie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_test.h"

uint16_t		test_get_id_flag_file(char *tmp)
{
	uint16_t flag;

	flag = FALSE;
	(ft_strcmp(tmp, TEST_STRB) == 0) ? flag = (TEST_B) : 0;
	(ft_strcmp(tmp, TEST_STRC) == 0) ? flag = (TEST_C) : 0;
	(ft_strcmp(tmp, TEST_STRD) == 0) ? flag = (TEST_D) : 0;
	(ft_strcmp(tmp, TEST_STRE) == 0) ? flag = (TEST_E) : 0;
	(ft_strcmp(tmp, TEST_STRF) == 0) ? flag = (TEST_F) : 0;
	(ft_strcmp(tmp, TEST_STRG) == 0) ? flag = (TEST_G) : 0;
	(ft_strcmp(tmp, TEST_STRL) == 0) ? flag = (TEST_L) : 0;
	(ft_strcmp(tmp, TEST_STRP) == 0) ? flag = (TEST_P) : 0;
	(ft_strcmp(tmp, TEST_STRR) == 0) ? flag = (TEST_R) : 0;
	(ft_strcmp(tmp, TEST_STRS) == 0) ? flag = (TEST_S) : 0;
	(ft_strcmp(tmp, TEST_STRSS) == 0) ? flag = (TEST_SS) : 0;
	(ft_strcmp(tmp, TEST_STRU) == 0) ? flag = (TEST_U) : 0;
	(ft_strcmp(tmp, TEST_STRW) == 0) ? flag = (TEST_W) : 0;
	(ft_strcmp(tmp, TEST_STRX) == 0) ? flag = (TEST_X) : 0;
	return (flag);
}

uint16_t		test_get_id_flag_str(char *tmp)
{
	uint16_t flag;

	flag = FALSE;
	(ft_strcmp(tmp, TEST_STRZ) == 0) ? flag = (TEST_Z) : 0;
	(ft_strcmp(tmp, TEST_STREQUAL) == 0) ? flag = (TEST_EQUAL) : 0;
	(ft_strcmp(tmp, TEST_STRDIFF) == 0) ? flag = (TEST_DIFF) : 0;
	return (flag);
}

uint16_t		test_get_id_flag_nbr(char *tmp)
{
	uint16_t flag;

	flag = FALSE;
	(ft_strcmp(tmp, TEST_STREQ) == 0) ? flag = (TEST_EQ) : 0;
	(ft_strcmp(tmp, TEST_STRNE) == 0) ? flag = (TEST_NE) : 0;
	(ft_strcmp(tmp, TEST_STRGE) == 0) ? flag = (TEST_GE) : 0;
	(ft_strcmp(tmp, TEST_STRLT) == 0) ? flag = (TEST_LT) : 0;
	(ft_strcmp(tmp, TEST_STRLE) == 0) ? flag = (TEST_LE) : 0;
	(ft_strcmp(tmp, TEST_STRNO) == 0) ? flag = (TEST_NO) : 0;
	return (flag);
}

uint16_t		test_get_id_flag(char *tmp)
{
	uint16_t flag;

	flag = FALSE;
	if ((flag = test_get_id_flag_file(tmp)) != FALSE)
		return (flag);
	if ((flag = test_get_id_flag_str(tmp)) != FALSE)
		return (flag);
	if ((flag = test_get_id_flag_nbr(tmp)) != FALSE)
		return (flag);
	return (flag);
}

uint16_t		test_set_id_flag(char **s)
{
	uint16_t	flag;

	flag = FALSE;
	if (s[1] && (flag = test_get_id_flag(s[1])) != FALSE)
		return (flag);
	if (s[0] && (flag = test_get_id_flag(s[0])) != FALSE)
		return (flag);
	return (FALSE);
}
