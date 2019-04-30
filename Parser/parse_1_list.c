/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 04:54:38 by modaouch          #+#    #+#             */
/*   Updated: 2019/04/07 00:06:10 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

//follow set used here to determinate if $empty or not ...

void					complet_cmd(t_ast **ast, t_edit *line_e)
{
    ft_printf("--<complet_cmd>--\n");
    if (first_set(head_of_line(*ast), T_BANG, T_WORD, -1))
    {
        list_fct(ast, line_e);
        line_break_fct(ast, line_e);
    }
    if (first_set(head_of_line(*ast), T_EOF, -1))
        return ;
    else
    {
	    ft_printf("|%d|\n", head_of_line(*ast));
        //ast_insert_left(get_next_token(str_line), ast);//un nest matcher ??
        ft_putstr_fd("42sh syntax error.0.5\n", 2);//cree un error msg en var globale un genre de g_errmsg
        g_errorno = ER_SYNTAX;
        return ;
    }
 }

void					list_fct(t_ast **ast, t_edit *line_e)
{
    ft_printf("--<list_fct>--\n");

    if (first_set(head_of_line(*ast), T_BANG, T_WORD, -1))
    {
        and_or_fct(ast, line_e);
        list_prime_fct(ast, line_e);
    }
    else
    {
	    ft_printf("|%d|\n", head_of_line(*ast));
        //ast_insert_left(get_next_token(str_line), ast);//un nest matcher ??
        ft_putstr_fd("42sh syntax error.1\n", 2);//cree un error msg en var globale un genre de g_errmsg
        g_errorno = ER_SYNTAX;
        return ;
    }
}

void					list_prime_fct(t_ast **ast, t_edit *line_e)
{
    ft_printf("--<list_prime_fct>--\n");

    if (first_set(head_of_line(*ast), T_SEMI, T_AMPER, -1))
    {
        separator_op_fct(ast, line_e);
        list_dprime_fct(ast, line_e);
    }
    else if (first_set(head_of_line(*ast), T_NEWL, T_EOF, -1))
    {
        return ;
    }
    else
    {
	    ft_printf("|%d|\n", head_of_line(*ast));
        //ast_insert_left(get_next_token(str_line), ast);//un nest matcher ??
        ft_putstr_fd("42sh syntax error.2\n", 2);//cree un error msg en var globale un genre de g_errmsg
        g_errorno = ER_SYNTAX;
        return ;
    }
}

void                    list_dprime_fct(t_ast **ast, t_edit *line_e)
{
    ft_printf("--<list_dprime_fct>--\n");
    if (first_set(head_of_line(*ast), T_BANG, T_WORD, -1))
    {
        and_or_fct(ast, line_e);
        list_prime_fct(ast, line_e);
    }
    else if (first_set(head_of_line(*ast), T_NEWL, T_EOF, -1))
    {
        return ;
    }
    else
    {
	    ft_printf("|%d|\n", head_of_line(*ast));
        //ast_insert_left(get_next_token(str_line), ast);//un nest matcher ??
        ft_putstr_fd("42sh syntax error.3\n", 2);//check si je rentre, peut etre que c'est inutile et cree un error msg en var globale un genre de g_errmsg
        g_errorno = ER_SYNTAX;
        return ;
    }
}


//follow set used here to determinate if $empty or not ...

/*
*
* first :                                           follow:
*
* cmpt_cmd :  !, word                               cmpt_cmd:   EOF
* list:       !, word                               list:       newline, EOF
* list':      &, ;, EMPTY                           list':      newline, EOF
* list'':     !, newline, !, word, EMPTY            list'':     newline, EOF
* and_or:     !, word                               and_or:     &, ;, newline, EOF
* and_or':    &&, ||, &, ;, newline, EMPTY          and_or':    &, ;, newline, EOF
* and_or_op:  &&, ||                                and_or_op:  newline, !, word
* pipeline:   !, word                               pipeline:   &&, ||, &, ;, newline, EOF
* bang_opt:   !, word                               bang_opt:   word
* pipe_seq:   word                                  pipe_seq:   &&, ||, &, ;, newline, EOF
* pipe_seq':  |, &&, ||, ;, &, newline, |, EMPTY    pipe_seq':  &&, ||, &, ;, newline, EOF
* command:    word                                  command:    |, &&, ||, &, ;, newline, EOF
* linebreak:  newline, !, word                      linebreak:  word, !, EOF
* separ_op:   &, ;                                  separ_op:   !, word, newline, EOF
* newl_list:  newline                               newl_list:  word, !, EOF
* newl_list'  newline, word, EMPTY                  newl_list':  word, !, EOF
*
*/
