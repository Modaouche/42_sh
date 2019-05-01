/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_7_io_fct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 00:38:00 by modaouch          #+#    #+#             */
/*   Updated: 2019/04/07 00:39:54 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void        io_redirect_fct(t_ast **ast, t_edit *line_e)
{
    if (first_set(head_of_line(*ast), T_IO_NB, -1))
        io_number_opt_fct(ast, line_e);
    else if (first_set(head_of_line(*ast), T_GREAT, T_GREATAND, T_DGREAT,\
        T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS, T_LESSAND, T_DLESSDASH, -1))
        io_kind_fct(ast, line_e);
}

void        io_number_opt_fct(t_ast **ast, t_edit *line_e)
{
    if (first_set(head_of_line(*ast), T_IO_NB, -1))
        ast_insert_left(get_next_token(&(line_e->line), &(line_e->i)), ast);
}

void        io_kind_fct(t_ast **ast, t_edit *line_e)
{
    if (first_set(head_of_line(*ast), T_GREAT, T_GREATAND, T_DGREAT,\
        T_CLOBBER, T_LESSGREAT, T_LESS, T_LESSAND, -1))
    {
        io_file(ast, line_e);
    }
    else if (first_set(head_of_line(*ast), T_DLESSDASH, T_DLESS, -1))
    {
        io_here(ast, line_e);
    }
}

void        io_file(t_ast **ast, t_edit *line_e)
{
    if (first_set(head_of_line(*ast),T_GREAT, T_GREATAND, T_DGREAT,\
        T_CLOBBER, T_LESSGREAT, T_LESS, T_LESSAND, -1))
    {
        ast_insert_right(get_next_token(&(line_e->line), &(line_e->i)), ast);
        if (first_set(head_of_line(*ast), T_WORD, -1))
            ast_insert_left(get_next_token(&(line_e->line), &(line_e->i)), ast);
        else
        {
	        ft_printf("|%d|\n", head_of_line(*ast));
            //un nest matcher ??
            ft_putstr_fd("42sh syntax error.10\n", 2);//check si je rentre, peut etre que c'est inutile avec specifical message
            g_errorno = ER_SYNTAX;
            return ;//maybe an exit with error
        }
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

void        io_here(t_ast **ast, t_edit *line_e)
{
    if (first_set(head_of_line(*ast), T_DLESSDASH, T_DLESS, -1))
    {
        ast_insert_right(get_next_token(&(line_e->line), &(line_e->i)), ast);
        if (first_set(head_of_line(*ast), T_WORD, -1))
            ast_insert_left(get_next_token(&(line_e->line), &(line_e->i)), ast);
        else
        {
	        ft_printf("|%d|\n", head_of_line(*ast));
            //un nest matcher ??
            ft_putstr_fd("42sh syntax error.10\n", 2);//check si je rentre, peut etre que c'est inutile avec specifical message
            g_errorno = ER_SYNTAX;
            return ;//maybe an exit with error
        }
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