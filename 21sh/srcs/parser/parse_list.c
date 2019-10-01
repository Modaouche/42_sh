/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 04:54:38 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 13:00:56 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	complet_cmd(t_edit *line_e)
{
	if (token_cmp(last_token(0), T_BANG, T_WORD, T_GREAT, T_GREATAND,\
		T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS, T_LESSAND,\
		T_DLESSDASH, T_IO_NB, T_ASGMT_WRD, -1)
		&& g_shell.errorno != ER_SYNTAX)
	{
		list_fct(line_e);
		line_break_fct(line_e);
	}
	else
	{
		g_shell.errorno = ER_SYNTAX;
		return ;
	}
}

void	list_fct(t_edit *line_e)
{
	if (token_cmp(last_token(0), T_BANG, T_WORD, T_GREAT, T_GREATAND,\
		T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS, T_LESSAND,\
		T_DLESSDASH, T_IO_NB, T_ASGMT_WRD, -1)
		&& g_shell.errorno != ER_SYNTAX)
	{
		and_or_fct(line_e);
		list_prime_fct(line_e);
	}
	else
	{
		g_shell.errorno = ER_SYNTAX;
		return ;
	}
}

void	list_prime_fct(t_edit *line_e)
{
	if (token_cmp(last_token(0), T_SEMI, T_AMPER, -1)\
			&& g_shell.errorno != ER_SYNTAX)
	{
		separator_op_fct(line_e);
		list_dprime_fct(line_e);
	}
	else if (!token_cmp(last_token(0), T_NEWL, T_EOF, -1))
	{
		g_shell.errorno = ER_SYNTAX;
		return ;
	}
}

void	list_dprime_fct(t_edit *line_e)
{
	if (token_cmp(last_token(0), T_BANG, T_WORD, T_GREAT, T_GREATAND,\
		T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS, T_LESSAND,\
		T_DLESSDASH, T_IO_NB, T_ASGMT_WRD, -1)
			&& g_shell.errorno != ER_SYNTAX)
	{
		and_or_fct(line_e);
		list_prime_fct(line_e);
	}
	else if (!token_cmp(last_token(0), T_NEWL, T_EOF, -1))
	{
		g_shell.errorno = ER_SYNTAX;
		return ;
	}
}
