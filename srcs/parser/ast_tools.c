/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 03:36:28 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/23 04:29:45 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_ast       *ast_new(t_token *tok)
{
	t_ast *tree;

	if (!(tree = (t_ast *)ft_memalloc(sizeof(t_ast))))
		to_exit(ER_MALLOC);
	tree->token = tok;
	return (tree);
}

void        ast_left_insert(t_token *tok)
{
	t_ast *new;
	t_ast_ptr *ast_head;

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

void	ast_right_insert(t_token *tok)
{
	t_ast *new;
	t_ast *tmp;
	t_ast_ptr *ast_head;

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

void	ast_next_cmd(t_token *tok)
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
		bind_last_head();//here
	ast_head->curr_head = ast_head->curr_head->right;
}

void        infix_print_ast(t_ast *root)
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

void		rm_last_leaf(void)
{
	t_ast	*to_free;
	t_ast	*tmp;
	t_ast_ptr	*ast_head;

	ast_head = st_ast();
	tmp = ast_head->curr_head;
	if (!(ast_head->curr_head))
		return ;
	if (tmp->right)
	{
		while (tmp->right->right)
			tmp = tmp->right;
		to_free = tmp->right;
		tmp->right = tmp->right->left;
	}
	else
	{
		if (ast_head->root && tmp == ast_head->root->right)
			ft_printf("!! ast_head->root->right == ast_head->curr_head !!\n");
		ft_printf("Freeing ast_head->curr_head (%p)\n", ast_head->curr_head);
		to_free = tmp;
		ast_head->curr_head = tmp->left;
	}
	ft_strdel(&(to_free->token->lexeme));
	ft_memdel((void **)&(to_free->token));
	ft_memdel((void **)&(to_free));
	if (ast_head->root)
		ft_printf("ast_head->root->right == %p\n", ast_head->root->right);
}

void	assign_to_word(void)
{
	t_ast *last;

	last = last_node(0);
	if (token_cmp(last->token->tokind, T_ASGMT_WRD, -1))
		last->token->tokind = T_WORD;
}

t_ast	*get_curr_head(void)
{
	t_ast_ptr *ast_head;

	ast_head = st_ast();
	return (ast_head->curr_head);
}

void	ast_free(t_ast **root)
{
	t_ast *to_free;

	if (!root || !*root)
		return ;
	to_free = *root;
	ast_free(&(to_free->left));
	ast_free(&(to_free->right));
	ft_strdel(&(to_free->token->lexeme));
	ft_memdel((void **)&(to_free->token));
	ft_memdel((void **)&(to_free));
	*root = NULL;
}
