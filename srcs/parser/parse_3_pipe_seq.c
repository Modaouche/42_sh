/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3_pipe_seq.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 07:02:59 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/23 01:57:33 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void        pipeline_fct(t_ast **ast, t_edit *line_e)
{
	// ft_printf("--<pipeline_fct>--\n");
	if (first_set(head_of_line(*ast), T_BANG, T_WORD, T_GREAT, T_GREATAND,\
		T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND,\
		T_DLESSDASH, T_IO_NB, T_ASGMT_WRD, -1)
		&& g_errorno != ER_SYNTAX)
	{
		bang_fct(ast, line_e);
		pipe_sequence_fct(ast, line_e);
	}
	else if (!first_set(head_of_line(*ast), T_EOF, -1))
	{
		g_errorno = ER_SYNTAX;
		return ;
	}
}

void        bang_fct(t_ast **ast, t_edit *line_e)
{
	// ft_printf("--<bang_fct>--\n");
	if (first_set(head_of_line(*ast), T_BANG, -1) && g_errorno != ER_SYNTAX)
		ast_insert_left(get_next_token((const char **)&(line_e->line),\
		&(line_e->ofst)), ast);
}

void        pipe_sequence_fct(t_ast **ast, t_edit *line_e)
{
	// ft_printf("--<pipe_sequence_fct>--\n");
	if (first_set(head_of_line(*ast), T_WORD, T_GREAT, T_GREATAND, T_DGREAT,\
		T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND, T_DLESSDASH,\
		T_IO_NB, T_ASGMT_WRD, -1) && g_errorno != ER_SYNTAX)
	{
		command_fct(ast, line_e);
		pipe_sequence_prime_fct(ast, line_e);
	}
	else
	{
		g_errorno = ER_SYNTAX;
		return ;
	}
}

void        pipe_sequence_prime_fct(t_ast **ast, t_edit *line_e)
{
	// ft_printf("--<pipe_sequence_prime_fct>--\n");
	if (first_set(head_of_line(*ast), T_PIPE, -1) && g_errorno != ER_SYNTAX)
	{
		ast_insert_right(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);//inserer interieurement
		line_break_fct(ast, line_e);
		while (first_set(head_of_line(*ast), T_EOF, -1))
		{
			init_line(line_e);
			line_e->prompt_size = print_prompt(1);
			line_edition(line_e);
			if (!line_e->line)
				line_e->line = ft_memalloc(1);
			rm_last_leaf(ast);
			ast_insert_right(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
		}
		command_fct(ast, line_e);
		pipe_sequence_prime_fct(ast, line_e);
	}
	else if (!first_set(head_of_line(*ast), T_EOF, T_NEWL, T_AND_IF, T_OR_IF, T_SEMI, T_AMPER, -1))
	{
		g_errorno = ER_SYNTAX;
		return ;
	}
}
