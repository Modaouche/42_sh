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


void    check_opened_fd(t_job *j)
{
    if (fcntl(j->stdin, F_GETFL) == -1)
        close(j->stdin);
    if (fcntl(j->stdout, F_GETFL) == -1)
        close(j->stdout);
    if (fcntl(j->stderr, F_GETFL) == -1)
        close(j->stderr);
}

void    io_less(t_ast *ast, t_job *j)
{
    int fd;

    ft_printf("===[%d]===\n", ast->token->tokind);
    if ((fd = open(ast_get_lexeme(ast), O_CREAT | O_TRUNC | O_WRONLY, 0644)))
    {
        access_verification(ast_get_lexeme(ast));
        return ;
    }
    check_opened_fd(j);
    if (ast->left->token->tokind == T_IO_NB)
    {
        if (ast->left->token->tokind - 48 == 0)
             j->stdin = fd;
        if (ast->left->token->tokind - 48 == 1)
             j->stdout = fd;
        if (ast->left->token->tokind - 48 == 2)
             j->stderr = fd;
        return ;
    }
    j->stdin = fd;
}

void    io_dless(t_ast *ast, t_job *j)
{
    int     fd;
    char    *lex;

    ft_printf("===[%d]===\n", ast->token->tokind);
    if ((fd = memfd_create("dless", 0)))
    {
        g_shell.errorno = ER_UNKNOW;
        return ;
    }
    lex = ast_get_lexeme(ast);
    write(fd, lex, ft_strlen(lex));
    check_opened_fd(j);
    if (ast->left->token->tokind == T_IO_NB)
    {
        if (ast->left->token->tokind - 48 == 0)
             j->stdin = fd;
        if (ast->left->token->tokind - 48 == 1)
             j->stdout = fd;
        if (ast->left->token->tokind - 48 == 2)
             j->stderr = fd;
        return ;
    }
    j->stdin = fd;
}

void    io_lessand(t_ast *ast, t_job *j)
{
    int fd;

    ft_printf("===[%d]===\n", ast->token->tokind);
    fd = atoi(ast_get_lexeme(ast));
    check_opened_fd(j);
    if (ast->left->token->tokind == T_IO_NB)
    {
        if (ast->left->token->tokind - 48 == 0)
             j->stdin = fd;
        if (ast->left->token->tokind - 48 == 1)
             j->stdout = fd;
        if (ast->left->token->tokind - 48 == 2)
             j->stderr = fd;
        return ;
    }
    j->stdin = fd;
}
