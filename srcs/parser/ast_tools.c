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

void        ast_insert_left(t_token *tok, t_ast **root)//ptr > ** ?//rename in injection
{
	t_ast *tree;
	t_ast *tmp;

	tmp = *root;
	if (!tok || !(tree = ast_new(tok)))
		return ;//to_exit !
	if (!*root)
		*root = tree;
	else if (!(*root)->right)
	{
		tree->left = *root;
		*root = tree;
	}
	else if ((*root)->right)
	{
		while (tmp->right && tmp->right->right)
			tmp = tmp->right;
		tree->left = tmp->right;
		tmp->right = tree;
	}
}

void        ast_insert_right(t_token *tok, t_ast **root)//ptr > ** ?
{
	t_ast *tree;
	t_ast *tmp;

	tmp = *root;
	if (!tok || !(tree = ast_new(tok)))
		return ;//to_exit !
	while (tmp->right)
		tmp = tmp->right;
	tmp->right = tree;
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

void		rm_last_leaf(t_ast **root)
{
	t_ast *tmp;

	tmp = *root;
	if (!root || !*root)
	{
		ft_putendl_fd("root is NULL", 2);//to rm
		return ;
	}
	while (tmp->right && tmp->right->right)
		tmp = tmp->right;
	if (tmp->right)
	{
		ft_strdel(&(tmp->right->token->lexeme));
		ft_memdel((void *)tmp->right->token);
		ft_memdel((void *)tmp->right);
		tmp->right = NULL;
	}
}
