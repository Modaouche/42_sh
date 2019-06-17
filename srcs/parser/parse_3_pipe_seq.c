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
	printf( " %s %d\n", __FILE__, __LINE__);
	if (token_cmp(head_of_line(*ast), T_BANG, T_WORD, T_GREAT, T_GREATAND,\
		T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS, T_LESSAND,\
		T_DLESSDASH, T_IO_NB, T_ASGMT_WRD, -1)
		&& g_errorno != ER_SYNTAX)
	{
		if (token_cmp((*ast)->token->tokind, T_AND_IF, T_OR_IF, -1))
		{
			bang_fct(&(*ast)->right, line_e);
			pipe_sequence_fct(&(*ast)->right, line_e);
		}
		else
		{
			bang_fct(ast, line_e);
			pipe_sequence_fct(ast, line_e);
		}
	}
	else if (!token_cmp(head_of_line(*ast), T_EOF, -1))
		g_errorno = ER_SYNTAX;
}

void        bang_fct(t_ast **ast, t_edit *line_e)
{
	// ft_printf("--<bang_fct>--\n");
	printf( " %s %d\n", __FILE__, __LINE__);
	if (token_cmp(head_of_line(*ast), T_BANG, -1) && g_errorno != ER_SYNTAX)
		ast_left_insert(get_next_token(&(line_e->line),\
				&(line_e->ofst)), ast);
}

void        pipe_sequence_fct(t_ast **ast, t_edit *line_e)
{
	// ft_printf("--<pipe_sequence_fct>--\n");
	printf( " %s %d\n", __FILE__, __LINE__);
	if (token_cmp(head_of_line(*ast), T_WORD, T_GREAT, T_GREATAND, T_DGREAT,\
		T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND, T_DLESSDASH,\
		T_IO_NB, T_ASGMT_WRD, -1) && g_errorno != ER_SYNTAX)
	{
		command_fct(ast, line_e);
		pipe_sequence_prime_fct(ast, line_e);
	}
	else
		g_errorno = ER_SYNTAX;
}

void        pipe_sequence_prime_fct(t_ast **ast, t_edit *line_e)
{
	// ft_printf("--<pipe_sequence_prime_fct>--\n");
	printf( " %s %d\n", __FILE__, __LINE__);
	if (token_cmp(head_of_line(*ast), T_PIPE, -1) && g_errorno != ER_SYNTAX)
	{
		ast_right_insert(get_next_token(&(line_e->line),\
			&(line_e->ofst)), ast);
		line_break_fct(ast, line_e);
		while (token_cmp(head_of_line(*ast), T_EOF, -1))
		{
			init_line(line_e);
			line_e->prompt_size = print_prompt(1);
			line_edition(line_e);
			if (!line_e->line)
				line_e->line = ft_memalloc(1);
			rm_last_leaf(ast);
			ast_right_insert(get_next_token(&(line_e->line), &(line_e->ofst)), ast);
		}
		command_fct(&(*ast)->right, line_e);
		pipe_sequence_prime_fct(&(*ast)->right, line_e);
	}
	else if (!token_cmp(head_of_line(*ast), T_EOF, T_NEWL, T_AND_IF, T_OR_IF, T_SEMI, T_AMPER, -1))
		g_errorno = ER_SYNTAX;
}
