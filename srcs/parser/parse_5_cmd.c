/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_5_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 00:02:18 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/23 02:02:19 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void        command_fct(t_ast **ast, t_edit *line_e)
{
    // ft_printf("--<command_fct>--\n");
    if (first_set(head_of_line(*ast), T_WORD, -1))
    {
        ast_insert_left(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
        cmd_suffix_opt_fct(ast, line_e);
    }
    else if (first_set(head_of_line(*ast), T_GREAT, T_GREATAND,\
        T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND,\
        T_DLESSDASH, T_IO_NB, T_ASGMT_WRD, -1))
    {
        cmd_prefix_fct(ast, line_e);
        cmd_suffix_fct(ast, line_e);
    }
    else
    {
	    g_errorno = ER_SYNTAX;
        return ;
    }
}

void        cmd_suffix_fct(t_ast **ast, t_edit *line_e)
{
    if (first_set(head_of_line(*ast), T_WORD, -1) && g_errorno != ER_SYNTAX)
    {
        ast_insert_left(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
        cmd_suffix_opt_fct(ast, line_e);
    }
    else if (first_set(head_of_line(*ast),T_PIPE, T_AND_IF, T_OR_IF, T_AMPER, T_SEMI,\
        T_NEWL, T_EOF, -1))
        return ;//a virer ?? les empty il n y a pas de gestion d'erreur ? genre c est quand il y a un unempty que l'on check ?
    else
    {
        g_errorno = ER_SYNTAX;
        return ;
    }//a virer ?? les empty il n y a pas de gestion d'erreur ? genre c est quand il y a un unempty que l'on check ?
}

void        cmd_suffix_opt_fct(t_ast **ast, t_edit *line_e)
{
    if (first_set(head_of_line(*ast), T_WORD, T_GREAT, T_GREATAND, T_DGREAT,\
        T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS, T_LESSAND, T_DLESSDASH, T_IO_NB, -1)\
        && g_errorno != ER_SYNTAX)
        cmd_suffix_prime_fct(ast, line_e);        
    else if (first_set(head_of_line(*ast),T_PIPE, T_AND_IF, T_OR_IF, T_AMPER, T_SEMI,\
        T_NEWL, T_EOF, -1))
        return ;//a virer ?? les empty il n y a pas de gestion d'erreur ? genre c est quand il y a un unempty que l'on check ?
    else
    {
        g_errorno = ER_SYNTAX;
        return ;
    }//a virer ?? les empty il n y a pas de gestion d'erreur ? genre c est quand il y a un unempty que l'on check ?
}
