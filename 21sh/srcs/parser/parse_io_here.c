/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io_here.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:19:05 by araout            #+#    #+#             */
/*   Updated: 2019/09/23 12:37:53 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		io_here_loop(t_edit *line_e, t_io_here *a)
{
	init_line(line_e);
	g_shell.prompt_size = print_prompt(6);
	line_edition(line_e);
	if (!line_e->line || !line_e->line[0])
		line_e->line = ft_strdup_del("\n", line_e->line);
	a->to_cmp = get_heredoc(line_e);
	if (a->begin && ft_strcmp(a->heredoc->lexeme, a->to_cmp->lexeme))
		ast_right_insert(a->to_cmp);
	else if (ft_strcmp(a->heredoc->lexeme, a->to_cmp->lexeme))
	{
		if (!a->next)
		{
			a->next = get_curr_head();
			a->next = a->next->right;
		}
		a->next->token->lexeme = ft_strjoin_free(a->next->token->lexeme,\
			"\n", 1);
		a->next->token->lexeme = ft_strjoin_free(a->next->token->lexeme,\
			a->to_cmp->lexeme, 3);
		ft_memdel((void **)&(a->to_cmp));
	}
	else
		return (-1);
	a->begin = 0;
	return (0);
}

void			io_here_t_word(t_edit *line_e, t_io_here *a)
{
	a->cpy = ft_strdup(&line_e->line[line_e->ofst]);
	while (1)
	{
		if (io_here_loop(line_e, a) != 0)
			break ;
	}
	ft_strdel(&line_e->line);
	ft_strdel(&(a->heredoc->lexeme));
	ft_memdel((void **)&(a->heredoc));
	line_e->line = a->cpy;
	ast_left_insert(get_next_token(&(line_e->line),\
		&(line_e->ofst)));
}

void			io_here(t_edit *line_e)
{
	t_io_here	a;

	a.begin = 1;
	a.next = NULL;
	if (token_cmp(last_token(0), T_DLESSDASH, T_DLESS, -1)\
			&& g_shell.errorno != ER_SYNTAX)
	{
		a.heredoc = get_next_token(&(line_e->line), &(line_e->ofst));
		assign_to_word();
		(a.heredoc->tokind == T_ASGMT_WRD) ? a.heredoc->tokind = T_WORD : 0;
		if (a.heredoc->tokind == T_WORD)
		{
			while (io_here_loop(line_e, &a) != -1)
				;
		}
		else
		{
			ft_memdel((void **)&(a.heredoc));
			g_shell.errorno = ER_SYNTAX;
		}
	}
}
