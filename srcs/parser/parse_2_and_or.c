/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2_and_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 07:02:47 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/23 02:15:40 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void        and_or_fct(t_ast **ast, t_edit *line_e)
{
    // ft_printf("--<and_or_fct>--\n");

    if (first_set(head_of_line(*ast), T_BANG, T_WORD, T_GREAT, T_GREATAND,\
        T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND, T_DLESSDASH, T_IO_NB,\
        T_ASGMT_WRD, -1) && g_errorno != ER_SYNTAX)
    {
        pipeline_fct(ast, line_e);
        and_or_prime_fct(ast, line_e);
    }
}

void        and_or_prime_fct(t_ast **ast, t_edit *line_e)
{
    // ft_printf("--<and_or_prime_fct>--\n");
    if (first_set(head_of_line(*ast), T_AND_IF, T_OR_IF, -1)\
        && g_errorno != ER_SYNTAX)
    {
        and_or_op_fct(ast, line_e);
        line_break_fct(ast, line_e);
        while (first_set(head_of_line(*ast), T_EOF, -1))
        {
	        init_line(line_e);
            rm_last_leaf(ast);
	        while (!line_e->line)
            {
	            line_e->prompt_size = print_prompt(head_of_line(*ast));
                line_edition(line_e);
            }
    	    ast_insert_right(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
        }
        pipeline_fct(ast, line_e);
        and_or_prime_fct(ast, line_e);
    }
    else if (first_set(head_of_line(*ast), T_AMPER, T_SEMI, T_NEWL, T_EOF, -1))
        return ;
    else
    {
    	g_errorno = ER_SYNTAX;
        return ;
    }
}

void        and_or_op_fct(t_ast **ast, t_edit *line_e)
{
    // ft_printf("--<and_or_op_fct>--\n");
    if (first_set(head_of_line(*ast), T_AND_IF, T_OR_IF, -1) && g_errorno != ER_SYNTAX)//to rm ??
	    ast_insert_right(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
}
