/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_fct_p.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:56:41 by modaouch          #+#    #+#             */
/*   Updated: 2019/03/02 10:50:59 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
#define SHELL_H

#include "shell.h"
/*
* TabPtr de fonction à mettre en place
*/

static t_key_code	keytab[] = {
		{S_KEY_ARW_LEFT, &key_arrow},
        {S_KEY_ARW_RIGHT, &key_arrow},
        //{S_KEY_ARW_BOT, &key_arrow},
        //{S_KEY_ARW_TOP, &key_arrow},
        {S_KEY_PRINTABLE, &key_printable},
		{S_KEY_ERASE, &key_erase},
        //{S_KEY_CTRL_D, &key_quit},
        //{S_KEY_ESC, &key_quit},
        //{S_KEY_RET, &key_return},
        {S_KEY_NONE, NULL}
	};

#endif