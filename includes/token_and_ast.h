/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_and_ast.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 21:51:47 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/11 18:44:13 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum
{
						T_NONE,
						T_AMPER,
    					T_SEMI,
    					T_AND_IF,
    					T_OR_IF,
    					T_BANG,
    					T_PIPE,
                        T_WORD,
                        T_NEWL,
                        T_LESS,
                        T_LESSAND,
                        T_GREAT,
                        T_GREATAND,
                        T_DGREAT,
                        T_LESSGREAT,
                        T_CLOBBER,
                        T_DLESS,
                        T_DLESSDASH,
                        T_ASGMT_WRD,
                        T_IO_NB,
                        T_ERROR,
                        T_EOF,
}						token;

typedef struct			s_token
{
	char				*lexeme;
	token				tokind;
}						t_token;

typedef struct      s_ast
{
	t_token         *token;
    struct s_ast    *right;
    struct s_ast    *left;
}                   t_ast;

typedef void	    	(*t_token_tab)(t_token *token, const char *line, int *i);

extern t_token_tab g_token_tab[128];

#endif