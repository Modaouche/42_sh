/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_7_io_fct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 00:38:00 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 09:58:37 by modaouch         ###   ########.fr       */
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
        ast_insert_left(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
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
        ast_insert_right(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
        if (first_set(head_of_line(*ast), T_WORD, -1))
            ast_insert_left(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
        else
        {
	        ft_printf("|%d|\n", head_of_line(*ast));
            ft_putstr_fd("42sh syntax error.12\n", 2);//check si je rentre, peut etre que c'est inutile avec specifical message
            g_errorno = ER_SYNTAX;
            return ;//maybe an exit with error
        }
    }
}

void        io_here(t_ast **ast, t_edit *line_e)
{
    //t_token *heredoc;
    //char *cpy;

    if (first_set(head_of_line(*ast), T_DLESSDASH, T_DLESS, -1))
    {
        //heredoc = get_next_token((const char **)&(line_e->line), &(line_e->ofst));
        ast_insert_right(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
        //if (first_set(heredoc->tokind, T_WORD, -1))
        if (first_set(head_of_line(*ast), T_WORD, -1))
        {
            /*
            cpy = ft_strdup(&line_e->line[line_e->ofst]);
            while (ft_strcmp(heredoc->lexeme, line_e->line))
            {
                init_line(line_e);
	            while (line_e->line)
                {
	                line_e->prompt_size = print_prompt(6);
                    line_edition(line_e);
                }
                if (ft_strcmp(heredoc->lexeme, line_e->line))
    	            ast_insert_left(get_heredoc((const char **)&(line_e->line), &(line_e->ofst)), ast);
            }
            ft_strdel(line_e->line);
            line_e->line = cpy;
            */
            ast_insert_right(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
        }
        else
        {
	        ft_printf("|%d|\n", head_of_line(*ast));
            ft_putstr_fd("42sh syntax error.13\n", 2);//check si je rentre, peut etre que c'est inutile avec specifical message
            g_errorno = ER_SYNTAX;
            return ;//maybe an exit with error
        }
    }
}