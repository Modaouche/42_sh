/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_6_cmd_prime.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 00:36:50 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/23 02:03:50 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void        cmd_suffix_prime_fct(t_ast **ast, t_edit *line_e)
{
	printf( " %s %d\n", __FILE__, __LINE__);
	if (token_cmp(head_of_line(*ast), T_WORD, -1) && g_errorno != ER_SYNTAX)
	{
		if (token_cmp((*ast)->token->tokind, T_GREAT, T_GREATAND,\
			T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS,\
			T_LESSAND, T_DLESSDASH, T_SEMI, T_AMPER, -1))
		 	(!((*ast)->right))
				? ast_right_insert(get_next_token(\
				&(line_e->line), &(line_e->ofst)), ast)\
				: ast_left_insert(get_next_token(\
				&(line_e->line), &(line_e->ofst)),\
				&(*ast)->right);
		else
			ast_left_insert(get_next_token(&(line_e->line),\
				&(line_e->ofst)), ast);
		cmd_suffix_dprime_fct(ast, line_e);
	}
	else if (token_cmp(head_of_line(*ast), T_GREAT, T_GREATAND,\
			T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS,\
			T_LESSAND, T_DLESSDASH, T_IO_NB, -1) && g_errorno != ER_SYNTAX)
	{
		io_redirect_fct(ast, line_e);
		cmd_suffix_dprime_fct(ast, line_e);
	}
	else
		g_errorno = ER_SYNTAX;
}

void        cmd_suffix_dprime_fct(t_ast **ast, t_edit *line_e)
{
	printf( " %s %d\n", __FILE__, __LINE__);
	if (token_cmp(head_of_line(*ast), T_WORD, -1) && g_errorno != ER_SYNTAX)
	{
		if (token_cmp((*ast)->token->tokind, T_GREAT, T_GREATAND,\
			T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS,\
			T_LESSAND,T_DLESSDASH, T_OR_IF, T_AND_IF, T_PIPE, -1))
		 	(!((*ast)->right))
				? ast_right_insert(get_next_token(\
				&(line_e->line), &(line_e->ofst)), ast)\
				: ast_left_insert(get_next_token(\
				&(line_e->line), &(line_e->ofst)),\
				&(*ast)->right);
		else
			ast_left_insert(get_next_token(&(line_e->line),\
				&(line_e->ofst)), ast);
		cmd_suffix_dprime_fct(ast, line_e);
	}
	else if (token_cmp(head_of_line(*ast), T_GREAT, T_GREATAND,\
			T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND,\
			T_DLESSDASH, T_IO_NB, -1) && g_errorno != ER_SYNTAX)
	{
		io_redirect_fct(ast, line_e);
		cmd_suffix_dprime_fct(ast, line_e);
	}
}

void        cmd_prefix_fct(t_ast **ast, t_edit *line_e)
{
	printf( " %s %d\n", __FILE__, __LINE__);
	if (token_cmp(head_of_line(*ast), T_ASGMT_WRD, -1)\
			&& g_errorno != ER_SYNTAX)
	{
		if (token_cmp((*ast)->token->tokind, T_GREAT, T_GREATAND,\
			T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS,\
			T_LESSAND,T_DLESSDASH, T_OR_IF, T_AND_IF, T_PIPE, -1))
		 	(!((*ast)->right))
				? ast_right_insert(get_next_token(\
				&(line_e->line), &(line_e->ofst)), ast)\
				: ast_left_insert(get_next_token(\
				&(line_e->line), &(line_e->ofst)),\
				&(*ast)->right);
		else
			ast_left_insert(get_next_token(&(line_e->line),\
				&(line_e->ofst)), ast);
		cmd_prefix_prime_fct(ast, line_e);
	}
	else if (token_cmp(head_of_line(*ast), T_GREAT, T_GREATAND,\
			T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS, T_LESSAND,\
			T_DLESSDASH,T_IO_NB, -1) && g_errorno != ER_SYNTAX)
	{
		io_redirect_fct(ast, line_e);
		cmd_prefix_prime_fct(ast, line_e);
	}
	else
		g_errorno = ER_SYNTAX;
}

void        cmd_prefix_prime_fct(t_ast **ast, t_edit *line_e)
{
	printf( " %s %d\n", __FILE__, __LINE__);
	if (token_cmp(head_of_line(*ast), T_ASGMT_WRD, -1)\
		&& g_errorno != ER_SYNTAX)
	{
		if (token_cmp((*ast)->token->tokind, T_GREAT, T_GREATAND,\
			T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS,\
			T_LESSAND,T_DLESSDASH, T_OR_IF, T_AND_IF, T_PIPE, -1))
		 	(!((*ast)->right))
				? ast_right_insert(get_next_token(\
				&(line_e->line), &(line_e->ofst)), ast)\
				: ast_left_insert(get_next_token(\
				&(line_e->line), &(line_e->ofst)),\
				&(*ast)->right);
		else
			ast_left_insert(get_next_token(&(line_e->line),\
				&(line_e->ofst)), ast);
		cmd_prefix_prime_fct(ast, line_e);
	}
	else if (token_cmp(head_of_line(*ast), T_GREAT, T_GREATAND,\
			T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,T_DLESS,\
			T_LESSAND, T_DLESSDASH,T_IO_NB, -1) && g_errorno != ER_SYNTAX)
	{
		io_redirect_fct(ast, line_e);
		cmd_prefix_prime_fct(ast, line_e);
	}
}
