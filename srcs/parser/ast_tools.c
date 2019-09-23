/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 03:36:28 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 11:30:16 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_ast		*ast_new(t_token *tok)
{
	t_ast	*tree;

	if (!(tree = (t_ast *)ft_memalloc(sizeof(t_ast))))
		to_exit(ER_MALLOC);
	tree->token = tok;
	return (tree);
}

void		ast_left_insert(t_token *tok)
{
	t_ast		*new;
	t_ast_ptr	*ast_head;

	ast_head = st_ast();
	if (!tok || !(new = ast_new(tok)))
		to_exit(ER_MALLOC);
	if (!(ast_head->curr_head))
		ast_head->curr_head = new;
	else
	{
		new->left = ast_head->curr_head;
		ast_head->curr_head = new;
	}
}

void		ast_right_insert(t_token *tok)
{
	t_ast		*new;
	t_ast		*tmp;
	t_ast_ptr	*ast_head;

	ast_head = st_ast();
	if (!tok || !(new = ast_new(tok)))
		to_exit(ER_MALLOC);
	if (!(ast_head->curr_head))
		ast_head->curr_head = new;
	else
	{
		tmp = last_node(0);
		tmp->right = new;
	}
}

void		ast_next_cmd(t_token *tok)
{
	t_ast		*new;
	t_ast_ptr	*ast_head;
	t_ast		*last;

	ast_head = st_ast();
	last = last_node(0);
	new = NULL;
	if (!tok || !(new = ast_new(tok)))
		to_exit(ER_MALLOC);
	tok = ft_memdup(last->token, sizeof(*tok));
	tok->lexeme = ft_strdup(last->token->lexeme);
	rm_last_leaf();
	ast_left_insert(tok);
	ast_head->curr_head->right = new;
	if (!ast_head->root)
		ast_head->root = ast_head->curr_head;
	else
		bind_last_head();
	ast_head->curr_head = ast_head->curr_head->right;
}

void		infix_print_ast(t_ast *root)
{
	if (!root)
		return ;
	infix_print_ast(root->left);
	if (root->token->lexeme)
		ft_printf("- %d [%s]", root->token->tokind, root->token->lexeme);
	else
		ft_printf("- %d [NO_THING] -", root->token->tokind);
	infix_print_ast(root->right);
}
