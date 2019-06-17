/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_7_io_fct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 00:38:00 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/23 02:08:40 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void        io_redirect_fct(t_ast **ast, t_edit *line_e)
{
	printf( " %s %d\n", __FILE__, __LINE__);
	if (token_cmp(head_of_line(*ast), T_GREAT, T_GREATAND, T_DGREAT,T_IO_NB,\
		T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS, T_LESSAND,\
		T_DLESSDASH, -1) && g_errorno != ER_SYNTAX)
	{
		io_number_opt_fct(ast, line_e);
		io_kind_fct(ast, line_e);
	}
}

void        io_number_opt_fct(t_ast **ast, t_edit *line_e)
{
	printf( " %s %d\n", __FILE__, __LINE__);
	if (token_cmp(head_of_line(*ast), T_IO_NB, -1) && g_errorno != ER_SYNTAX)
	{
		if (token_cmp((*ast)->token->tokind, T_GREAT, T_GREATAND,\
			T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS, T_LESSAND,\
			T_DLESSDASH, T_SEMI, T_AMPER, -1))
		 	(!((*ast)->right))
				? ast_right_insert(get_next_token(\
				&(line_e->line), &(line_e->ofst)), ast)\
				: ast_left_insert(get_next_token(\
				&(line_e->line), &(line_e->ofst)),\
				&(*ast)->right);
		else
			ast_left_insert(get_next_token(&(line_e->line),\
				&(line_e->ofst)), ast);
	}
}

void        io_kind_fct(t_ast **ast, t_edit *line_e)
{
	printf( " %s %d\n", __FILE__, __LINE__);
	if (token_cmp(head_of_line(*ast), T_GREAT, T_GREATAND, T_DGREAT,\
		T_CLOBBER, T_LESSGREAT, T_LESS, T_LESSAND, -1)\
		&& g_errorno != ER_SYNTAX)
		io_file(ast, line_e);
	else if (token_cmp(head_of_line(*ast), T_DLESSDASH, T_DLESS, -1)\
		&& g_errorno != ER_SYNTAX)
		io_here(ast, line_e);
	else
	{
		g_errorno = ER_SYNTAX;
		return ;
	}
}

void        io_file(t_ast **ast, t_edit *line_e)
{
	if (token_cmp(head_of_line(*ast),T_GREAT, T_GREATAND, T_DGREAT,\
		T_CLOBBER, T_LESSGREAT, T_LESS, T_LESSAND, -1)\
		&& g_errorno != ER_SYNTAX)
	{
		ast_right_insert(get_next_token(&(line_e->line),\
			&(line_e->ofst)), ast);
		if (token_cmp(head_of_line(*ast), T_WORD, -1))
			ast_left_insert(get_next_token(&(line_e->line), &(line_e->ofst)), ast);
		else
			g_errorno = ER_SYNTAX;
	}
}

void        io_here(t_ast **ast, t_edit *line_e)
{
	printf( " %s %d\n", __FILE__, __LINE__);
	t_token *heredoc;
	char	*cpy;
	t_token *to_cmp;
	int	begin;

	begin = 1;
	if (token_cmp(head_of_line(*ast), T_DLESSDASH, T_DLESS, -1) && g_errorno != ER_SYNTAX)
	{
		heredoc = get_next_token(&(line_e->line), &(line_e->ofst));//leaks?
		if (heredoc->tokind == T_WORD)
		{
			cpy = ft_strdup(&line_e->line[line_e->ofst]);
			while (1)
			{
				printf("loop\n");
				init_line(line_e);
				line_e->prompt_size = print_prompt(6);
				line_edition(line_e);
				if (!line_e->line || !line_e->line[0])
					line_e->line = ft_strdup_del("\n", line_e->line);
				to_cmp = get_heredoc(line_e);
				if (begin && ft_strcmp(heredoc->lexeme, to_cmp->lexeme))
					ast_right_insert(to_cmp, ast);
				else if (ft_strcmp(heredoc->lexeme, to_cmp->lexeme))
				{
					(*ast)->right->token->lexeme\
						= ft_strjoin_free((*ast)->right->token->lexeme,\
						"\n", 1);
					(*ast)->right->token->lexeme\
						= ft_strjoin_free((*ast)->right->token->lexeme,\
						to_cmp->lexeme, 3);
					ft_memdel((void **)&to_cmp);
				}
				else
					break ;
				begin = 0;
			}
			ft_strdel(&line_e->line);
			ft_strdel(&(heredoc->lexeme));
			ft_memdel((void **)&heredoc);
			line_e->line = cpy;
			ast_left_insert(get_next_token(&(line_e->line),\
				&(line_e->ofst)), ast);
		}
		else
		{
			ft_memdel((void **)&heredoc);
			g_errorno = ER_SYNTAX;
		}
	}
}//gerer les heredocd (voir la doc opengrp) et and , once the ctrl v + j set, go make a parser for \n.                  //c'est a revoir...
