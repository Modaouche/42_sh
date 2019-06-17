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
		return (0);
	tree->token = tok;
	return (tree);
}

void        ast_left_insert(t_token *tok, t_ast **node)
{
	t_ast *new;

	if (!tok || !(new = ast_new(tok)))
		return ;//to_exit !
	if (!*node)
		*node = new;
	else
	{
		new->left = *node;
		*node = new;
	}
}

void	ast_right_insert(t_token *tok, t_ast **node)
{
	t_ast *new;
	t_ast *tmp;

	tmp = *node;
	if (!tok || !(new = ast_new(tok)))
		return ;//to_exit !
	if (!*node)
		*node = new;
	else
	{
		tmp = head_of_node(*node);
		tmp->right = new;
	}
}

void	ast_next_cmd(t_token *tok, t_ast **node)
{
	t_ast		*new;
	t_ast_ptr	*ast_head;
	t_ast		*elem;

	elem = head_of_node(*node);
	if (!tok || !(new = ast_new(tok)))
		return ;//to_exit !
	tok = ft_memdup(elem->token, sizeof(*tok));
	tok->lexeme = ft_strdup(elem->token->lexeme);
	infix_print_ast(*node);
	ft_printf("\nbef ^^\naft vv\n");

	rm_last_leaf(node);
	infix_print_ast(*node);
	ft_printf("\na> [%s] ;? [%d]\n", (*node)->token->lexeme, tok->tokind);
	ast_left_insert(elem->token, node);

	ft_printf("c> [%s]\n", (*node)->token->lexeme);
	(*node)->right = new;
	ast_head = st_ast();
	if (!ast_head->root)
	{
		ft_printf("unNULL ok\n");
		ast_head->root = *node;
	}
	*node = (*node)->right;
	ast_head->curr_head = *node;
}

void        infix_print_ast(t_ast *root)
{
	if (!root)
		return ;
	infix_print_ast(root->left);
	if (root->token->lexeme)
		ft_printf("- %d [%s] ", root->token->tokind, root->token->lexeme);
	else
		ft_printf("- %d [NO_THING] -", root->token->tokind);
	infix_print_ast(root->right);

}

void		rm_last_leaf(t_ast **node)
{
	t_ast *to_free;
	t_ast *tmp;

	tmp = *node;
	if (!node || !*node)
	{
		ft_putendl_fd("node is NULL", 2);//to rm
		return ;
	}
	if ((*node)->right)
	{
		while (tmp->right->right)
			tmp = tmp->right;
		to_free = tmp->right;
		tmp->right = (*node)->right->left;
	}
	else
	{
		to_free = *node;
		*node = (*node)->left;
	}
	ft_strdel(&(to_free->token->lexeme));
	ft_memdel((void *)to_free->token);
	ft_memdel((void *)to_free);
}
