/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2_and_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 07:02:47 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/13 19:59:11 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void        and_or_fct(t_ast **ast, t_edit *line_e)
{
    ft_printf("--<and_or_fct>--\n");

    if (first_set(head_of_line(*ast), T_BANG, T_WORD, T_GREAT, T_GREATAND,\
        T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND, T_DLESSDASH, T_IO_NB,\
        T_ASGMT_WRD, -1))
    {
        pipeline_fct(ast, line_e);
        and_or_prime_fct(ast, line_e);
    }
}

void        and_or_prime_fct(t_ast **ast, t_edit *line_e)
{
    ft_printf("--<and_or_prime_fct>--\n");
    if (first_set(head_of_line(*ast), T_AND_IF, T_OR_IF, -1))
    {
        and_or_op_fct(ast, line_e);
        line_break_fct(ast, line_e);
        if (first_set(head_of_line(*ast), T_EOF, -1)) //while ??
        {
	        rm_last_leaf(ast);
	        init_line(line_e);
	        prompt_extend();//to complete with nested prompt maybe or not...
	        line_edition(line_e);
	        ft_putendl("");
    	    ast_insert_right(get_next_token((const char **)&(line_e->line), &(line_e->i)), ast);
        }
        pipeline_fct(ast, line_e);
        and_or_prime_fct(ast, line_e);
    }
    else if (first_set(head_of_line(*ast), T_AMPER, T_SEMI, T_NEWL, T_EOF, -1))
    {
        return ;
    }
    else
    {
	ft_printf("|%d|\n", head_of_line(*ast));
       //ast_insert_left(get_next_token(str_line), ast);//un nest matcher ??
        ft_putstr_fd("42sh syntax error.4\n", 2);//check si je rentre, peut etre que c'est inutile
        g_errorno = ER_SYNTAX;
        return ;//maybe an exit with error
    }
}

void        and_or_op_fct(t_ast **ast, t_edit *line_e)
{
    ft_printf("--<and_or_op_fct>--\n");
    if (first_set(head_of_line(*ast), T_AND_IF, T_OR_IF, -1))//to rm ??
	    ast_insert_right(get_next_token((const char **)&(line_e->line), &(line_e->i)), ast);
}
