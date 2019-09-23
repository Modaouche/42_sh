/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_suffix_dprime_fct.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:00:21 by araout            #+#    #+#             */
/*   Updated: 2019/09/23 12:03:14 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		cmd_suffix_dprime_fct_cmp(t_edit *line_e, t_ast_ptr *ast_head,\
		t_ast *save)
{
	if (token_cmp(ast_head->curr_head->token->tokind, T_GREAT, T_GREATAND,\
				T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS,\
				T_LESSAND, T_DLESSDASH, T_OR_IF, T_AND_IF, T_PIPE, -1))
	{
		if (save->right)
		{
			ast_head->curr_head = ast_head->curr_head->right;
			ast_left_insert(get_next_token(&(line_e->line),\
						&(line_e->ofst)));
			save->right = ast_head->curr_head;
			ast_head->curr_head = save;
		}
		else
			ast_left_insert(get_next_token(&(line_e->line),\
						&(line_e->ofst)));
	}
	else
		ast_left_insert(get_next_token(&(line_e->line),\
					&(line_e->ofst)));
	cmd_suffix_dprime_fct(line_e);
}

void			cmd_suffix_dprime_fct(t_edit *line_e)
{
	t_ast_ptr	*ast_head;
	t_ast		*save;

	ast_head = st_ast();
	save = ast_head->curr_head;
	assign_to_word();
	if (token_cmp(last_token(0), T_WORD, -1) && g_shell.errorno != ER_SYNTAX)
		cmd_suffix_dprime_fct_cmp(line_e, ast_head, save);
	else if (token_cmp(last_token(0), T_GREAT, T_GREATAND,\
				T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS, T_LESSAND,\
				T_DLESSDASH, T_IO_NB, -1) && g_shell.errorno != ER_SYNTAX)
	{
		io_redirect_fct(line_e);
		cmd_suffix_dprime_fct(line_e);
	}
}
