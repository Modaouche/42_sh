/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_parse_cmd_prime.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 00:36:50 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 12:09:45 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		cmd_prefix_prime_fct_cmp(t_edit *line_e, t_ast_ptr *ast_head,\
		t_ast *save, t_token *lookahead)
{
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
		ast_left_insert(lookahead);
	cmd_prefix_prime_fct(line_e);
}

void			cmd_prefix_prime_fct(t_edit *line_e)
{
	t_ast_ptr	*ast_head;
	t_ast		*save;
	t_token		*lookahead;

	ast_head = st_ast();
	save = ast_head->curr_head;
	if (token_cmp(last_token(0), T_ASGMT_WRD, -1)\
			&& g_shell.errorno != ER_SYNTAX)
	{
		lookahead = get_next_token(&(line_e->line), &(line_e->ofst));
		cmd_prefix_prime_fct_cmp(line_e, ast_head, save, lookahead);
	}
	else if (token_cmp(last_token(0), T_GREAT, T_GREATAND,\
				T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS,\
				T_LESSAND, T_DLESSDASH, T_IO_NB, -1)\
				&& g_shell.errorno != ER_SYNTAX)
	{
		io_redirect_fct(line_e);
		cmd_prefix_prime_fct(line_e);
	}
}
