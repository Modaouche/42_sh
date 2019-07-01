/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_parse_io_fct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 00:38:00 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/23 02:08:40 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void        io_redirect_fct(t_edit *line_e)
{
	//printf( " %s %d\n", __FILE__, __LINE__);
	if (token_cmp(last_token(0), T_GREAT, T_GREATAND, T_DGREAT, T_IO_NB,\
		T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS, T_LESSAND,\
		T_DLESSDASH, -1) && g_errorno != ER_SYNTAX)
	{
		io_number_opt_fct((line_e));
		io_kind_fct((line_e));
	}
}

void        io_number_opt_fct(t_edit *line_e)
{
	t_ast_ptr	*ast_head;
	t_ast		*save;
	t_token		*lookahead;

	ast_head = st_ast();
	save = ast_head->curr_head;
	//printf( " %s %d\n", __FILE__, __LINE__);
	if (token_cmp(last_token(0), T_IO_NB, -1) && g_errorno != ER_SYNTAX)
	{
		lookahead = get_next_token(&(line_e->line), &(line_e->ofst));
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
			ast_left_insert(lookahead);//in one fct
	}
}

void        io_kind_fct(t_edit *line_e)
{
	//printf( " %s %d\n", __FILE__, __LINE__);
	if (token_cmp(last_token(0), T_GREAT, T_GREATAND, T_DGREAT,\
		T_CLOBBER, T_LESSGREAT, T_LESS, T_LESSAND, -1)\
		&& g_errorno != ER_SYNTAX)
		io_file((line_e));
	else if (token_cmp(last_token(0), T_DLESSDASH, T_DLESS, -1)\
		&& g_errorno != ER_SYNTAX)
		io_here((line_e));
	assign_to_word();
}

void        io_file(t_edit *line_e)
{	
	t_ast_ptr	*ast_head;
	t_ast		*save;
	t_token		*lookahead;

	ast_head = st_ast();
	save = ast_head->curr_head;
	//printf( " %s %d\n", __FILE__, __LINE__);
	if (token_cmp(last_token(0),T_GREAT, T_GREATAND, T_DGREAT,\
		T_CLOBBER, T_LESSGREAT, T_LESS, T_LESSAND, -1)\
		&& g_errorno != ER_SYNTAX)
	{
		ast_right_insert(get_next_token(&(line_e->line),\
			&(line_e->ofst)));
		assign_to_word();
		if (token_cmp(last_token(0), T_WORD, -1))
		{
			//ft_printf("head -> %s", ast_head->curr_head->token->lexeme);
			lookahead = get_next_token(&(line_e->line), &(line_e->ofst));
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
				ast_left_insert(lookahead);//in one fct
		}
		else
			g_errorno = ER_SYNTAX;
	}
}

void        io_here(t_edit *line_e)// after look at this part
{
	t_token *heredoc;
	char	*cpy;
	t_token *to_cmp;
	int	begin;
	t_ast		*next;

	begin = 1;
	next = NULL;
	//printf( " %s %d\n", __FILE__, __LINE__);
	if (token_cmp(last_token(0), T_DLESSDASH, T_DLESS, -1) && g_errorno != ER_SYNTAX)
	{
		heredoc = get_next_token(&(line_e->line), &(line_e->ofst));//leaks?
		assign_to_word();
		(heredoc->tokind == T_ASGMT_WRD) ? heredoc->tokind = T_WORD : 0;
		if (heredoc->tokind == T_WORD)
		{
			cpy = ft_strdup(&line_e->line[line_e->ofst]);
			while (1)
			{
				init_line(line_e);
				line_e->prompt_size = print_prompt(6);
				line_edition(line_e);
				if (!line_e->line || !line_e->line[0])
					line_e->line = ft_strdup_del("\n", line_e->line);
				to_cmp = get_heredoc(line_e);
				if (begin && ft_strcmp(heredoc->lexeme, to_cmp->lexeme))
					ast_right_insert(to_cmp);
				else if (ft_strcmp(heredoc->lexeme, to_cmp->lexeme))
				{
					if (!next)
					{
						next = get_curr_head();
						next = next->right;
					}
					next->token->lexeme\
						= ft_strjoin_free(next->token->lexeme,\
						"\n", 1);
					next->token->lexeme\
						= ft_strjoin_free(next->token->lexeme,\
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
				&(line_e->ofst)));
		}
		else
		{
			ft_memdel((void **)&heredoc);
			g_errorno = ER_SYNTAX;
		}
	}
}//gerer les heredocd (voir la doc opengrp) et and , once the ctrl v + j set, go make a parser for \n.                  //c'est a revoir...
