/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tools_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:27:41 by araout            #+#    #+#             */
/*   Updated: 2019/09/23 11:31:57 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ast_free(t_ast **root)
{
	t_ast	*to_free;

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

void	assign_to_word(void)
{
	t_ast	*last;

	last = last_node(0);
	if (token_cmp(last->token->tokind, T_ASGMT_WRD, -1))
		last->token->tokind = T_WORD;
}

t_ast	*get_curr_head(void)
{
	t_ast_ptr	*ast_head;

	ast_head = st_ast();
	return (ast_head->curr_head);
}

void	rm_last_leaf(void)
{
	t_ast		*to_free;
	t_ast		*tmp;
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
