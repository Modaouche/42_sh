/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_parse_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 00:02:18 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/23 02:02:19 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void        command_fct(t_edit *line_e)
{
	t_ast_ptr	*ast_head;
	t_ast		*save;
	t_token		*lookahead;

	ast_head = st_ast();
	save = ast_head->curr_head;
	//printf( " %s %d\n", __FILE__, __LINE__);
	if (token_cmp(last_token(0), T_WORD, -1))
	{
		lookahead = get_next_token(&(line_e->line), &(line_e->ofst));
		if (token_cmp(ast_head->curr_head->token->tokind, T_GREAT,\
			T_GREATAND, T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,\
			T_DLESS, T_LESSAND, T_DLESSDASH, T_PIPE, T_AND_IF,\
			T_OR_IF, -1)\
			&& !token_cmp(lookahead->tokind, T_GREAT, T_GREATAND,\
			T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS,\
			T_LESSAND, T_DLESSDASH, T_PIPE, T_AND_IF, T_OR_IF, -1))
		{
			ast_head->curr_head = ast_head->curr_head->right;
			ast_left_insert(lookahead);
			save->right = ast_head->curr_head;
			ast_head->curr_head = save;
		}
		else 
			ast_left_insert(lookahead);//in one fct
		cmd_suffix_opt_fct(line_e);
	}
	else if (token_cmp(last_token(0), T_GREAT, T_GREATAND, T_DGREAT,\
		T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND,\
		T_DLESSDASH, T_IO_NB, T_ASGMT_WRD, -1))
	{
		cmd_prefix_fct(line_e);
		cmd_suffix_fct(line_e);
	}
	else
		g_shell.errorno = ER_SYNTAX;
}

void        cmd_suffix_fct(t_edit *line_e)
{
	t_ast_ptr	*ast_head;
	t_ast		*save;

	ast_head = st_ast();
	save = ast_head->curr_head;
	//printf( " %s %d\n", __FILE__, __LINE__);
	if (token_cmp(last_token(0), T_WORD, -1) && g_shell.errorno != ER_SYNTAX)
	{
		if (token_cmp(ast_head->curr_head->token->tokind, T_GREAT, T_GREATAND,\
			T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS,\
			T_LESSAND, T_DLESSDASH, T_AND_IF, T_OR_IF, -1))
		{
		 	if (save->right)
				ast_head->curr_head\
				= ast_head->curr_head->right;
			ast_left_insert(get_next_token(&(line_e->line),\
					&(line_e->ofst)));
			save->right = ast_head->curr_head;
			ast_head->curr_head = save;
		}
		else
			ast_left_insert(get_next_token(&(line_e->line),\
				&(line_e->ofst)));
		cmd_suffix_opt_fct(line_e);
	}
	else if (!token_cmp(last_token(0),T_PIPE, T_AND_IF, T_OR_IF,\
			T_AMPER, T_SEMI, T_NEWL, T_EOF, -1))
		g_shell.errorno = ER_SYNTAX;
}

void        cmd_suffix_opt_fct(t_edit *line_e)
{
	//printf( " %s %d\n", __FILE__, __LINE__);
	assign_to_word();
	if (token_cmp(last_token(0), T_WORD, T_GREAT, T_GREATAND, T_DGREAT,\
		T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS, T_LESSAND,\
		T_DLESSDASH, T_IO_NB, -1) && g_shell.errorno != ER_SYNTAX)
		cmd_suffix_prime_fct(line_e);        
	else if (!token_cmp(last_token(0), T_PIPE, T_AND_IF, T_OR_IF,\
			T_AMPER, T_SEMI, T_NEWL, T_EOF, -1))
		g_shell.errorno = ER_SYNTAX;
}
