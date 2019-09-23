/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:26:51 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 07:09:03 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H

# include "shell.h"
# define ENUM_LEN 9

typedef enum
{
	NO_ERROR,
	ER_DBACCES,
	ER_DBINFO,
	ER_NOT_TTY,
	ER_SYNTAX,
	ER_FORK,
	ER_EXECVE,
	ER_MALLOC,
	ER_PIPE,
	ER_ACCES,
	ER_ISDIR,
	ER_NOENT,
	ER_WAITPID,
	ER_CHILD
}	t_errorno;

void					le_exit(uint8_t bt);
void					to_exit(uint8_t bt);
void					error_msg(char *cmd);

#endif
