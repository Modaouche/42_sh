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

//compound litteral
//execve("/bin/dash", (char*[]){"bash", "-c", "cat", "/etc/passwd", NULL}, NULL)

t_token *ast_get_lexeme(t_ast *ast)
{
    ast = ast->right;
    while (ast && ast->left)
        ast = ast->left;
    return (ast->token);
}

void    io_great(t_ast *ast, t_job *j)
{
    int fd;
    int io_nb;
    t_token   *prev_tok;

    ft_printf("===GREAT===\n");
    prev_tok = ast->left->token;
    if ((fd = open(ast_get_lexeme(ast)->lexeme,\
            O_CREAT | O_TRUNC | O_WRONLY, 0644)) < 0)
    {
        access_verification(ast_get_lexeme(ast)->lexeme);
        return ;
    }
    ft_printf("gr fd = %d\n", fd);
    if (is_redir_exec(prev_tok->tokind))
        if (ast->left && ast->left->right)
            prev_tok = ast->left->right->token; 
    if (prev_tok->tokind == T_IO_NB)
    {
        io_nb = ft_atoi(prev_tok->lexeme);
        ft_printf("dgr io = %d\n", io_nb);
        check_opened_fd(j, io_nb, fd);
        return ;
    }
    check_opened_fd(j, 1, fd);
}


void    io_dgreat(t_ast *ast, t_job *j)
{
    int fd;
    int io_nb;
    t_token   *prev_tok;

    ft_printf("===DGREAT===\n");
    prev_tok = ast->left->token;
    if ((fd = open(ast_get_lexeme(ast)->lexeme, O_CREAT | O_WRONLY, 0644)) < 0)
    {
        access_verification(ast_get_lexeme(ast)->lexeme);
        return ;
    }
    ft_printf("dgr fd = %d\n", fd);
    lseek(fd, 0, SEEK_END);
    if (is_redir_exec(prev_tok->tokind))
        if (ast->left && ast->left->right)
            prev_tok = ast->left->right->token; 
    if (prev_tok->tokind == T_IO_NB)
    {
        io_nb = ft_atoi(prev_tok->lexeme);
        ft_printf("dgr io = %d\n", io_nb);
        check_opened_fd(j, io_nb, fd);
        return ;
    }
    check_opened_fd(j, 1, fd);
}

void    io_greatand(t_ast *ast, t_job *j)
{
    int fd;
    int io_nb;
    t_token   *prev_tok;

    ft_printf("===GREATAND===\n");
    prev_tok = ast->left->token;
    fd = atoi(ast_get_lexeme(ast)->lexeme);
    ft_printf("gr_and fd = %d\n", fd);
    if (is_redir_exec(prev_tok->tokind))
        if (ast->left && ast->left->right)
            prev_tok = ast->left->right->token; 
    if (prev_tok->tokind == T_IO_NB)
    {
        io_nb = ft_atoi(prev_tok->lexeme);
        ft_printf("dgr io = %d\n", io_nb);
        check_opened_fd(j, io_nb, fd);
        return ;
    }
    check_opened_fd(j, 1, fd);
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
