/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_4_line_brk.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 07:04:29 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 01:29:46 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void        line_break_fct(t_ast **ast, t_edit *line_e)
{
    ft_printf("--<line_break_fct>--\n");
    if (first_set(head_of_line(*ast), T_NEWL, -1))
    {
        newline_list_fct(ast, line_e);
    }
    else if (first_set(head_of_line(*ast), T_BANG, T_WORD, T_GREAT, T_GREATAND,\
        T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND, T_DLESSDASH, T_IO_NB,\
        T_ASGMT_WRD, T_EOF, -1))
    {
        return ;
    }
    else
    {
	    ft_printf("|%d|\n", head_of_line(*ast));
       	//let it//ast_insert_left(get_next_token(str_line), ast);//un nest matcher ??
        ft_putstr_fd("42sh syntax error.8\n", 2);//check si je rentre, peut etre que c'est inutile avec specifical message
        g_errorno = ER_SYNTAX;
        return ;//maybe an exit with error
    }
}

void        separator_op_fct(t_ast **ast, t_edit *line_e)
{
    ft_printf("--<separator_op_fct>--\n");
    if (first_set(head_of_line(*ast), T_SEMI, T_AMPER, -1))
        ast_insert_right(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
    else
    {
	    ft_printf("|%d|\n", head_of_line(*ast));
        //ast_insert_left(get_next_token(&(line_e->line), &(line_e->ofst)), ast);//un nest matcher ??
        ft_putstr_fd("42sh syntax error.9\n", 2);//check si je rentre, peut etre que c'est inutile avec specifical message
        g_errorno = ER_SYNTAX;
        return ;//maybe an exit with error
    }
}

void        newline_list_fct(t_ast **ast, t_edit *line_e)
{
    ft_printf("--<newline_list_fct>--\n");
    if (first_set(head_of_line(*ast), T_NEWL, -1))
        ast_insert_left(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);//un nest matcher ??
    newline_list_prime_fct(ast, line_e);
}

void        newline_list_prime_fct(t_ast **ast, t_edit *line_e)
{
    ft_printf("--<newline_list_prime_fct>--\n");
    if (first_set(head_of_line(*ast), T_NEWL, -1))
        ast_insert_left(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
    if (first_set(head_of_line(*ast), T_NEWL, -1))
        newline_list_prime_fct(ast, line_e);
    else if (first_set(head_of_line(*ast), T_BANG, T_WORD, T_GREAT, T_GREATAND,\
        T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND, T_DLESSDASH, T_IO_NB,\
        T_ASGMT_WRD, T_EOF, -1))
    {
        return ;
    }
    else
    {
	    ft_printf("|%d|\n", head_of_line(*ast));
        //ast_insert_left(get_next_token(str_line), ast);//un nest matcher ??
        ft_putstr_fd("42sh syntax error.10\n", 2);//check si je rentre, peut etre que c'est inutile avec specifical message
        g_errorno = ER_SYNTAX;
        return ;//maybe an exit with error
    }
}
