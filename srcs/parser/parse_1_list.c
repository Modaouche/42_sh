/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 04:54:38 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/23 01:53:57 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

//follow set used here to determinate if $empty or not ...

void					complet_cmd(t_ast **ast, t_edit *line_e)
{
	// ft_printf("--<complet_cmd>--\n");
	if (first_set(head_of_line(*ast), T_BANG, T_WORD, T_GREAT, T_GREATAND,\
		T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND,\
		T_DLESSDASH, T_IO_NB, T_ASGMT_WRD, -1)
		&& g_errorno != ER_SYNTAX)
	{
		list_fct(ast, line_e);
		line_break_fct(ast, line_e);
	}
	else
	{
		g_errorno = ER_SYNTAX;
		return ;
	}
}

void					list_fct(t_ast **ast, t_edit *line_e)
{
	// ft_printf("--<list_fct>--\n");
	if (first_set(head_of_line(*ast), T_BANG, T_WORD, T_GREAT, T_GREATAND,\
		T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS, T_LESSAND,\
		T_DLESSDASH, T_IO_NB, T_ASGMT_WRD, -1)
		&& g_errorno != ER_SYNTAX)
	{
		and_or_fct(ast, line_e);
		list_prime_fct(ast, line_e);
	}
	else
	{
		g_errorno = ER_SYNTAX;
		return ;
	}
}

void					list_prime_fct(t_ast **ast, t_edit *line_e)
{
	// ft_printf("--<list_prime_fct>--\n");
	if (first_set(head_of_line(*ast), T_SEMI, T_AMPER, -1)\
      && g_errorno != ER_SYNTAX)
	{
    separator_op_fct(ast, line_e);
    list_dprime_fct(ast, line_e);
	}
  else if (!first_set(head_of_line(*ast), T_NEWL, T_EOF, -1))
  {
    g_errorno = ER_SYNTAX;
    return ;
  }
}

void          list_dprime_fct(t_ast **ast, t_edit *line_e)
{
	// ft_printf("--<list_dprime_fct>--\n");
	if (first_set(head_of_line(*ast), T_BANG, T_WORD, T_GREAT, T_GREATAND,\
		T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND,\
		T_DLESSDASH, T_IO_NB, T_ASGMT_WRD, -1)
		&& g_errorno != ER_SYNTAX)
	{
		and_or_fct(ast, line_e);
		list_prime_fct(ast, line_e);
	}
	else if (!first_set(head_of_line(*ast), T_NEWL, T_EOF, -1))
	{
		g_errorno = ER_SYNTAX;
		return ;
	}
}
