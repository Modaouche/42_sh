/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_4_line_brk.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 07:04:29 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/23 02:00:22 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void        line_break_fct(t_ast **ast, t_edit *line_e)
{
    // ft_printf("--<line_break_fct>--\n");

    if (first_set(head_of_line(*ast), T_NEWL, -1) && g_errorno != ER_SYNTAX)
    {
        newline_list_fct(ast, line_e);
    }
    else if (first_set(head_of_line(*ast), T_BANG, T_WORD, T_GREAT, T_GREATAND,\
        T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND, T_DLESSDASH, T_IO_NB,\
        T_ASGMT_WRD, T_EOF, -1))
        return ;
    else
    {
	    g_errorno = ER_SYNTAX;
        return ;
    }
}

void        separator_op_fct(t_ast **ast, t_edit *line_e)
{
    // ft_printf("--<separator_op_fct>--\n");
    if (first_set(head_of_line(*ast), T_SEMI, T_AMPER, -1) && g_errorno != ER_SYNTAX)
        ast_insert_right(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
    else
    {
	    g_errorno = ER_SYNTAX;
        return ;
    }
}

void        newline_list_fct(t_ast **ast, t_edit *line_e)
{
    // ft_printf("--<newline_list_fct>--\n");
    
    if (first_set(head_of_line(*ast), T_NEWL, -1) && g_errorno != ER_SYNTAX)
        ast_insert_left(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);//un nest matcher ??
    newline_list_prime_fct(ast, line_e);
}

void        newline_list_prime_fct(t_ast **ast, t_edit *line_e)
{
    // ft_printf("--<newline_list_prime_fct>--\n");
    
    if (first_set(head_of_line(*ast), T_NEWL, -1 && g_errorno != ER_SYNTAX))
        ast_insert_left(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
    if (first_set(head_of_line(*ast), T_NEWL, -1) && g_errorno != ER_SYNTAX)
        newline_list_prime_fct(ast, line_e);
    else if (first_set(head_of_line(*ast), T_BANG, T_WORD, T_GREAT, T_GREATAND,\
        T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND, T_DLESSDASH, T_IO_NB,\
        T_ASGMT_WRD, T_EOF, -1))
        return ;
    else
    {
	   g_errorno = ER_SYNTAX;
        return ;
    }
}
