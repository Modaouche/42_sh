/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_6_cmd_prime.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 00:36:50 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/23 02:03:50 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void        cmd_suffix_prime_fct(t_ast **ast, t_edit *line_e)
{
    if (first_set(head_of_line(*ast), T_WORD, -1) && g_errorno != ER_SYNTAX)
    {
        ast_insert_left(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
        cmd_suffix_dprime_fct(ast, line_e);
    }
    else if (first_set(head_of_line(*ast), T_GREAT, T_GREATAND,\
        T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND,\
        T_DLESSDASH, T_IO_NB, -1) && g_errorno != ER_SYNTAX)
    {
        io_redirect_fct(ast, line_e);
        cmd_suffix_dprime_fct(ast, line_e);

    }
    else
    {
	    g_errorno = ER_SYNTAX;
        return ;
    }
}

void        cmd_suffix_dprime_fct(t_ast **ast, t_edit *line_e)
{
    if (first_set(head_of_line(*ast), T_WORD, -1) && g_errorno != ER_SYNTAX)
    {
        ast_insert_left(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
        cmd_suffix_dprime_fct(ast, line_e);
    }
    else if (first_set(head_of_line(*ast), T_GREAT, T_GREATAND,\
        T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND,\
        T_DLESSDASH, T_IO_NB, -1) && g_errorno != ER_SYNTAX)
    {
        io_redirect_fct(ast, line_e);
        cmd_suffix_dprime_fct(ast, line_e);
    }
}

void        cmd_prefix_fct(t_ast **ast, t_edit *line_e)
{
    if (first_set(head_of_line(*ast), T_ASGMT_WRD, -1)\
		    && g_errorno != ER_SYNTAX)
    {
        ast_insert_left(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
        cmd_prefix_prime_fct(ast, line_e);
    }
    else if (first_set(head_of_line(*ast), T_GREAT, T_GREATAND,\
        T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND,\
        T_DLESSDASH,T_IO_NB, -1) && g_errorno != ER_SYNTAX)
    {
        io_redirect_fct(ast, line_e);
        cmd_prefix_prime_fct(ast, line_e);
    }
    else
    {
	    g_errorno = ER_SYNTAX;
        return ;
    }
}

void        cmd_prefix_prime_fct(t_ast **ast, t_edit *line_e)
{
    if (first_set(head_of_line(*ast), T_ASGMT_WRD, -1)\
		    && g_errorno != ER_SYNTAX)
    {
        ast_insert_left(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
        cmd_prefix_prime_fct(ast, line_e);
    }
    else if (first_set(head_of_line(*ast), T_GREAT, T_GREATAND,\
        T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND,\
        T_DLESSDASH,T_IO_NB, -1) && g_errorno != ER_SYNTAX)
    {
        io_redirect_fct(ast, line_e);
        cmd_prefix_prime_fct(ast, line_e);
    }
}
