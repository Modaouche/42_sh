/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe_seq.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 07:02:59 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 12:50:28 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void		pipeline_fct_init(t_ast_ptr **ast_head, t_ast **save)
{
	*ast_head = st_ast();
	*save = (*ast_head)->curr_head;
}

void		pipeline_fct(t_edit *line_e)
{
	t_ast_ptr	*ast_head;
	t_ast		*save;

	pipeline_fct_init(&ast_head, &save);
	if (token_cmp(last_token(0), T_BANG, T_WORD, T_GREAT, T_GREATAND,\
				T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS, T_LESSAND,\
				T_DLESSDASH, T_IO_NB, T_ASGMT_WRD, -1)
			&& g_shell.errorno != ER_SYNTAX)
	{
		if (token_cmp(save->token->tokind, T_AND_IF, T_OR_IF, -1))
		{
			ast_head->curr_head = ast_head->curr_head->right;
			bang_fct(line_e);
			pipe_sequence_fct(line_e);
			save->right = ast_head->curr_head;
			ast_head->curr_head = save;
		}
		else
		{
			bang_fct(line_e);
			pipe_sequence_fct(line_e);
		}
	}
	else if (!token_cmp(last_token(0), T_EOF, -1))
		g_shell.errorno = ER_SYNTAX;
}

void		bang_fct(t_edit *line_e)
{
	if (token_cmp(last_token(0), T_BANG, -1) && g_shell.errorno != ER_SYNTAX)
		ast_left_insert(get_next_token(&(line_e->line),\
					&(line_e->ofst)));
}

void		pipe_sequence_fct(t_edit *line_e)
{
	if (token_cmp(last_token(0), T_WORD, T_GREAT, T_GREATAND, T_DGREAT,\
				T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS, T_LESSAND,\
				T_DLESSDASH, T_IO_NB, T_ASGMT_WRD, -1)\
			&& g_shell.errorno != ER_SYNTAX)
	{
		command_fct(line_e);
		pipe_sequence_prime_fct(line_e);
	}
	else
		g_shell.errorno = ER_SYNTAX;
}

void		pipe_sequence_prime_fct(t_edit *line_e)
{
	if (token_cmp(last_token(0), T_PIPE, -1) && g_shell.errorno != ER_SYNTAX)
	{
		ast_right_insert(get_next_token(&(line_e->line),\
					&(line_e->ofst)));
		line_break_fct(line_e);
		while (token_cmp(last_token(0), T_EOF, -1))
		{
			init_line(line_e);
			g_shell.prompt_size = print_prompt(1);
			line_edition(line_e);
			if (!line_e->line)
				(!(line_e->line = ft_memalloc(1))) ? to_exit(1) : 0;
			rm_last_leaf();
			ast_right_insert(get_next_token(&(line_e->line), &(line_e->ofst)));
		}
		command_fct(line_e);
		pipe_sequence_prime_fct(line_e);
	}
	else if (!token_cmp(last_token(0), T_EOF, T_NEWL, T_AND_IF, T_OR_IF,\
				T_SEMI, T_AMPER, -1))
		g_shell.errorno = ER_SYNTAX;
}
