/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_less.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 22:00:43 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 09:02:29 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "job.h"

void	io_less(t_ast *ast, t_job *j)
{
	int		fd;
	int		io_nb;
	t_token	*prev_tok;

	prev_tok = ast->left->token;
	if ((fd = open(ast_get_lexeme(ast)->lexeme, O_RDONLY, 0644)) < 0)
	{
		access_verification(ast_get_lexeme(ast)->lexeme);
		return ;
	}
	if (is_redir_exec(prev_tok->tokind))
		if (ast->left && ast->left->right)
			prev_tok = ast->left->right->token;
	if (prev_tok->tokind == T_IO_NB)
	{
		io_nb = ft_atoi(prev_tok->lexeme);
		check_opened_fd(j, io_nb, fd);
		return ;
	}
	check_opened_fd(j, 0, fd);
}

void	io_dless(t_ast *ast, t_job *j)
{
	int		fd;
	char	*lex;
	int		io_nb;
	t_token	*prev_tok;

	prev_tok = ast->left->token;
	lex = generate_random_filename("/tmp/dless_file");
	if ((fd = open(lex, O_CREAT | O_RDWR, 0777)) < 0)
	{
		ft_strdel(&lex);
		g_shell.errorno = ER_UNKNOW;
		return ;
	}
	unlink(lex);
	ft_strdel(&lex);
	lex = ast_get_lexeme(ast)->lexeme;
	write(fd, lex, ft_strlen(lex));
	lseek(fd, 0, SEEK_SET);
	if (prev_tok->tokind == T_IO_NB)
	{
		io_nb = ft_atoi(prev_tok->lexeme);
		check_opened_fd(j, io_nb, fd);
		return ;
	}
	check_opened_fd(j, 0, fd);
}

void	io_lessand(t_ast *ast, t_job *j)
{
	int		fd;
	int		io_nb;
	t_token	*prev_tok;

	prev_tok = ast->left->token;
	if ((fd = get_redir_fd(ast_get_lexeme(ast)->lexeme, 0)) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "./42sh : Bad file descriptor.");
		return ;
	}
	if (is_redir_exec(prev_tok->tokind))
		if (ast->left && ast->left->right)
			prev_tok = ast->left->right->token;
	if (prev_tok->tokind == T_IO_NB)
	{
		io_nb = ft_atoi(prev_tok->lexeme);
		check_opened_fd(j, io_nb, fd);
		return ;
	}
	check_opened_fd(j, 0, fd);
}
