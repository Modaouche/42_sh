/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_6_cmd_prime.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 00:36:50 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 10:02:21 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void        cmd_suffix_prime_fct(t_ast **ast, t_edit *line_e)
{
    if (first_set(head_of_line(*ast), T_WORD, -1))
    {
        ast_insert_left(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
        cmd_suffix_dprime_fct(ast, line_e);
    }
    else if (first_set(head_of_line(*ast), T_GREAT, T_GREATAND,\
        T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND,\
        T_DLESSDASH, T_IO_NB, -1))
    {
        io_redirect_fct(ast, line_e);
        cmd_suffix_dprime_fct(ast, line_e);

    }
    else
    {
	    ft_printf("|%d|\n", head_of_line(*ast));
        //un nest matcher ??
        ft_putstr_fd("42sh syntax error.10\n", 2);//check si je rentre, peut etre que c'est inutile avec specifical message
        g_errorno = ER_SYNTAX;
        return ;//maybe an exit with error
    }
}

void        cmd_suffix_dprime_fct(t_ast **ast, t_edit *line_e)
{
    if (first_set(head_of_line(*ast), T_WORD, -1))
    {
        ast_insert_left(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
        cmd_suffix_dprime_fct(ast, line_e);
    }
    else if (first_set(head_of_line(*ast), T_GREAT, T_GREATAND,\
        T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND,\
        T_DLESSDASH, T_IO_NB, -1))
    {
        io_redirect_fct(ast, line_e);
        cmd_suffix_dprime_fct(ast, line_e);
    }
}

void        cmd_prefix_fct(t_ast **ast, t_edit *line_e)
{
    if (first_set(head_of_line(*ast), T_ASGMT_WRD, -1))
    {
        ast_insert_left(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
        cmd_prefix_prime_fct(ast, line_e);
    }
    else if (first_set(head_of_line(*ast), T_GREAT, T_GREATAND,\
        T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND,\
        T_DLESSDASH,T_IO_NB, -1))
    {
        io_redirect_fct(ast, line_e);
        cmd_prefix_prime_fct(ast, line_e);
    }
    else
    {
	    ft_printf("|%d|\n", head_of_line(*ast));
        ft_putstr_fd("42sh syntax error.10.1\n", 2);//check si je rentre, peut etre que c'est inutile avec specifical message
        g_errorno = ER_SYNTAX;
        return ;//maybe an exit with error
    }
}

void        cmd_prefix_prime_fct(t_ast **ast, t_edit *line_e)
{
    if (first_set(head_of_line(*ast), T_ASGMT_WRD, -1))
    {
        ast_insert_left(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
        cmd_prefix_prime_fct(ast, line_e);
    }
    else if (first_set(head_of_line(*ast), T_GREAT, T_GREATAND,\
        T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND,\
        T_DLESSDASH,T_IO_NB, -1))
    {
        io_redirect_fct(ast, line_e);
        cmd_prefix_prime_fct(ast, line_e);
    }
}