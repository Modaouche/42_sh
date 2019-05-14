/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_5_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 00:02:18 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 02:49:25 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void        command_fct(t_ast **ast, t_edit *line_e)
{
    ft_printf("--<command_fct>--\n");
    if (first_set(head_of_line(*ast), T_WORD, -1))
    {
        ft_printf("[%s] nb> %d", line_e->line, line_e->ofst);
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
	    ft_printf("|%d|\n", head_of_line(*ast));
        //un nest matcher ??
        ft_putstr_fd("42sh syntax error.10\n", 2);//check si je rentre, peut etre que c'est inutile avec specifical message
        g_errorno = ER_SYNTAX;
        return ;//maybe an exit with error
    }
    //ft_printf("cmdfct|%d|\n", head_of_line(*ast));
}

void        cmd_suffix_fct(t_ast **ast, t_edit *line_e)
{
    if (first_set(head_of_line(*ast), T_WORD, -1))
    {
        ast_insert_left(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
        cmd_suffix_opt_fct(ast, line_e);
    }
    else if (first_set(head_of_line(*ast),T_PIPE, T_AND_IF, T_OR_IF, T_AMPER, T_SEMI,\
        T_NEWL, T_EOF, -1))
    {
        return ;
    }
    else
    {
        ft_printf("|%d|\n", head_of_line(*ast));
        //un nest matcher ??
        ft_putstr_fd("42sh syntax error.11 (<< >> error maybe)\n", 2);//check si je rentre, peut etre que c'est inutile avec specifical message
        g_errorno = ER_SYNTAX;
        return ;//maybe an exit with error
    }
}

void        cmd_suffix_opt_fct(t_ast **ast, t_edit *line_e)
{
    if (first_set(head_of_line(*ast), T_WORD, T_GREAT, T_GREATAND, T_DGREAT,\
        T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS, T_LESSAND, T_DLESSDASH, T_IO_NB, -1))
    {
        cmd_suffix_prime_fct(ast, line_e);        
    }
    else if (first_set(head_of_line(*ast),T_PIPE, T_AND_IF, T_OR_IF, T_AMPER, T_SEMI,\
        T_NEWL, T_EOF, -1))
    {
        return ;
    }
    else
    {
        ft_printf("|%d|\n", head_of_line(*ast));
        //un nest matcher ??
        ft_putstr_fd("42sh syntax error.12 (<< >> error maybe)\n", 2);//check si je rentre, peut etre que c'est inutile avec specifical message
        g_errorno = ER_SYNTAX;
        return ;//maybe an exit with error
    }
}
