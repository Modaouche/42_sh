/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_great.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 22:00:43 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 09:02:29 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "job.h"

char    *ast_get_lexeme(t_ast *ast)
{
    ast = ast->left;
    while (ast && ast->right)
        ast = ast->right;
    return (ast->token->lexeme);
}

void    io_great(t_ast *ast, t_job *j)
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
    j->stdout = fd;
}

void    io_dgreat(t_ast *ast, t_job *j)
{
    int fd;

    ft_printf("===[%d]===\n", ast->token->tokind);
    if ((fd = open(ast_get_lexeme(ast), O_CREAT | O_TRUNC | O_WRONLY, 0644)))
    {
        access_verification(ast_get_lexeme(ast));
        return ;
    }
    lseek(fd, 0, SEEK_END);
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
    j->stdout = fd;
}

void    io_greatand(t_ast *ast, t_job *j)
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
    j->stdout = fd;
}

void    io_lessgreat(t_ast *ast, t_job *j)
{
    (void)ast;
    (void)j;
    ft_printf_fd(STDERR_FILENO, "./42sh: This feature is not supported.");
    g_shell.errorno = ER_UNKNOW;
}

void    io_clobber(t_ast *ast, t_job *j)
{
    (void)ast;
    (void)j;
    ft_printf_fd(STDERR_FILENO, "./42sh: This feature is not supported.");
    g_shell.errorno = ER_UNKNOW;
}
