/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_brk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 07:04:29 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 13:00:48 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void		separator_op_fct(t_edit *line_e)
{
	if (token_cmp(last_token(0), T_SEMI, T_AMPER, -1)\
			&& g_shell.errorno != ER_SYNTAX)
		ast_next_cmd(get_next_token(&(line_e->line), &(line_e->ofst)));
	else
		g_shell.errorno = ER_SYNTAX;
}

void		line_break_fct(t_edit *line_e)
{
	if (token_cmp(last_token(0), T_NEWL, -1) && g_shell.errorno != ER_SYNTAX)
		newline_list_fct(line_e);
}

void		newline_list_fct(t_edit *line_e)
{
	if (token_cmp(last_token(0), T_NEWL, -1) && g_shell.errorno != ER_SYNTAX)
		ast_next_cmd(get_next_token(&(line_e->line), &(line_e->ofst)));
	newline_list_prime_fct(line_e);
}

void		newline_list_prime_fct(t_edit *line_e)
{
	if (token_cmp(last_token(0), T_NEWL, -1 && g_shell.errorno != ER_SYNTAX))
		ast_next_cmd(get_next_token(&(line_e->line), &(line_e->ofst)));
	if (token_cmp(last_token(0), T_NEWL, -1) && g_shell.errorno != ER_SYNTAX)
		newline_list_prime_fct(line_e);
	else if (!token_cmp(last_token(0), T_BANG, T_WORD, T_GREAT,\
				T_GREATAND, T_DGREAT, T_CLOBBER, T_LESSGREAT,\
				T_LESS, T_DLESS, T_LESSAND, T_DLESSDASH, T_IO_NB,\
				T_ASGMT_WRD, T_EOF, -1))
		g_shell.errorno = ER_SYNTAX;
}
