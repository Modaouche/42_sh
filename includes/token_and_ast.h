/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_and_ast.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 21:51:47 by modaouch          #+#    #+#             */
/*   Updated: 2019/07/06 17:40:49 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_AND_AST_H
# define TOKEN_AND_AST_H

typedef enum
{
	T_NONE,
	T_NEWL,
	T_OR_IF,
	T_AND_IF,
	T_AMPER,
	T_SEMI,
	T_PIPE,
	T_LESS,
	T_LESSAND,
	T_GREAT,
	T_GREATAND,
	T_DGREAT,
	T_LESSGREAT,
	T_CLOBBER,
	T_DLESS,
	T_DLESSDASH,
	T_BANG,
	T_WORD,
	T_ASGMT_WRD,
	T_IO_NB,
	T_EOF,
}	t_tok;

typedef struct		s_token
{
	char			*lexeme;
	t_tok			tokind;
}					t_token;

typedef struct		s_ast
{
	t_token			*token;
	struct s_ast	*right;
	struct s_ast	*left;
}					t_ast;

typedef struct		s_ast_ptr
{
	t_ast			*root;
	t_ast			*curr_head;
}					t_ast_ptr;

typedef void		(*t_token_tab)(t_token *token, char *line,\
			unsigned int *i);

extern t_token_tab	g_token_tab[128];

#endif
