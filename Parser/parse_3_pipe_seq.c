/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3_pipe_seq.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 07:02:59 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/11 14:31:28 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void        pipeline_fct(t_ast **ast, t_edit *line_e)
{
    ft_printf("--<pipeline_fct>--\n");
    if (first_set(head_of_line(*ast), T_BANG, T_WORD, T_GREAT, T_GREATAND,\
        T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND, T_DLESSDASH, T_IO_NB,\
        T_ASGMT_WRD, -1))
    {
        bang_fct(ast, line_e);
        pipe_sequence_fct(ast, line_e);
    }
    else if (first_set(head_of_line(*ast), T_EOF, -1))
    {
        return ;
    }
    else
    {
	    ft_printf("|%d|\n", head_of_line(*ast));
        ft_putstr_fd("42sh syntax error.5\n", 2);//check si je rentre, peut etre que c'est inutile
        g_errorno = ER_SYNTAX;
        return ;//maybe an exit with error
    }
}

void        bang_fct(t_ast **ast, t_edit *line_e)
{
    ft_printf("--<bang_fct>--\n");
    if (first_set(head_of_line(*ast), T_BANG, -1))//a voir si il faut faire un else
        ast_insert_left(get_next_token((const char **)&(line_e->line), &(line_e->i)), ast);
}

void        pipe_sequence_fct(t_ast **ast, t_edit *line_e)
{
    ft_printf("--<pipe_sequence_fct>--\n");
    if (first_set(head_of_line(*ast), T_WORD, T_GREAT, T_GREATAND, T_DGREAT,\
        T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND, T_DLESSDASH, T_IO_NB,\
        T_ASGMT_WRD, -1))
    {
        command_fct(ast, line_e);
        pipe_sequence_prime_fct(ast, line_e);
    }
    else
    {
	    ft_printf("|%d|\n", head_of_line(*ast));
        ft_putstr_fd("42sh syntax error.6\n", 2);//OK maybe
        g_errorno = ER_SYNTAX;
        return ;//maybe an exit with error
    }
}

void        pipe_sequence_prime_fct(t_ast **ast, t_edit *line_e)
{
    ft_printf("--<pipe_sequence_prime_fct>--\n");
    if (first_set(head_of_line(*ast), T_PIPE, -1))
    {
        ast_insert_right(get_next_token((const char **)&(line_e->line), &(line_e->i)), ast);
        line_break_fct(ast, line_e);
        if (first_set(head_of_line(*ast), T_EOF, -1))
        {
		    rm_last_leaf(ast);
		    init_line(line_e);
		    prompt_extend();//to complete with nested prompt
		    line_edition(line_e);//to free avant l ancien line_e maybe
		    ft_putendl("");
    	    ast_insert_right(get_next_token((const char **)&(line_e->line), &(line_e->i)), ast);
        }
	    command_fct(ast, line_e);
        pipe_sequence_prime_fct(ast, line_e);
    }
    else if (first_set(head_of_line(*ast), T_EOF, T_NEWL, T_AND_IF, T_OR_IF, T_SEMI, T_AMPER, -1))
    {
        return ;
    }
    else
    {
	    ft_printf("|%d|\n", head_of_line(*ast));
        ft_putstr_fd("42sh syntax error.7\n", 2);//check si je rentre, peut etre que c'est inutile
        g_errorno = ER_SYNTAX;
        return ;//maybe an exit with error
    }
}
