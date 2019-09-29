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
    ast = ast->right;
    while (ast && ast->left)
        ast = ast->left;
    return (ast->token->lexeme);
}

void    io_great(t_ast *ast, t_job *j)
{
    int fd;

    ft_printf("===GREAT===\n");
    if ((fd = open(ast_get_lexeme(ast), O_CREAT | O_TRUNC | O_WRONLY, 0644)) < 0)
    {
        access_verification(ast_get_lexeme(ast));
        return ;
    }
    if (ast->left->token->tokind == T_IO_NB)
    {
        if (ast->left->token->tokind - 48 == 0)
            check_opened_fd(j, 0, fd);
        if (ast->left->token->tokind - 48 == 1)
            check_opened_fd(j, 1, fd);
        if (ast->left->token->tokind - 48 == 2)
            check_opened_fd(j, 2, fd);
        return ;
    }
    check_opened_fd(j, 1, fd);
    j->stdout = fd;
}

void    io_dgreat(t_ast *ast, t_job *j)
{
    int fd;

    ft_printf("===DGREAT===\n");
    if ((fd = open(ast_get_lexeme(ast), O_CREAT | O_WRONLY, 0644)) < 0)
    {
        access_verification(ast_get_lexeme(ast));
        return ;
    }
    lseek(fd, 0, SEEK_END);
    if (ast->left->token->tokind == T_IO_NB)
    {
        if (ast->left->token->tokind - 48 == 0)
            check_opened_fd(j, 0, fd);
        if (ast->left->token->tokind - 48 == 1)
            check_opened_fd(j, 1, fd);
        if (ast->left->token->tokind - 48 == 2)
            check_opened_fd(j, 2, fd);
        return ;
    }
    check_opened_fd(j, 0, fd);
    j->stdout = fd;
}

void    io_greatand(t_ast *ast, t_job *j)
{
    int fd;

    ft_printf("===GREATAND===\n");
    fd = atoi(ast_get_lexeme(ast));
    if (ast->left->token->tokind == T_IO_NB)
    {
        if (ast->left->token->tokind - 48 == 0)
            check_opened_fd(j, 0, fd);
        if (ast->left->token->tokind - 48 == 1)
            check_opened_fd(j, 1, fd);
        if (ast->left->token->tokind - 48 == 2)
            check_opened_fd(j, 2, fd);
        return ;
    }
    check_opened_fd(j, 0, fd);
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
