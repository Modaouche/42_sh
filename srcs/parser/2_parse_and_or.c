/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parse_and_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 07:02:47 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/23 02:15:40 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void        and_or_fct(t_edit *line_e)
{
	//printf( " %s %d\n", __FILE__, __LINE__);
	if (token_cmp(last_token(0), T_BANG, T_WORD, T_GREAT, T_GREATAND,\
		T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND,\
		T_DLESSDASH, T_IO_NB, T_ASGMT_WRD, -1)\
		&& g_shell.errorno != ER_SYNTAX)
	{
		pipeline_fct(line_e);
		and_or_prime_fct(line_e);
	}
}

void        and_or_prime_fct(t_edit *line_e)
{
	//printf( " %s %d\n", __FILE__, __LINE__);
	if (token_cmp(last_token(0), T_AND_IF, T_OR_IF, -1)\
		&& g_shell.errorno != ER_SYNTAX)
	{
		and_or_op_fct(line_e);
		line_break_fct(line_e);
		while (token_cmp(last_token(0), T_EOF, -1))
		{
			init_line(line_e);
			rm_last_leaf();
			while (!line_e->line)
			{
				g_shell.prompt_size = print_prompt(last_token(0));
				line_edition(line_e);
			}
			ast_right_insert(get_next_token(&(line_e->line),\
				&(line_e->ofst)));
		}
		pipeline_fct(line_e);
		and_or_prime_fct(line_e);
	}
	else if (!token_cmp(last_token(0), T_AMPER, T_SEMI, T_NEWL, T_EOF, -1))
		g_shell.errorno = ER_SYNTAX;
}

void        and_or_op_fct(t_edit *line_e)
{
	//printf( " %s %d\n", __FILE__, __LINE__);
	ast_right_insert(get_next_token(&(line_e->line), &(line_e->ofst)));
}
