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


void    check_opened_fd(t_job *j, int io_nb, int fd)
{
    if ((j->stderr != STDERR_FILENO 
            && j->stdout != STDOUT_FILENO
            && j->stdin != STDIN_FILENO ) && io_nb == 0)
    {
        ft_printf("in close \n");
        close(j->stdin);
    }
    if(io_nb == 0)
    {
        ft_printf("in assi\n");
        j->stdin = fd;
    }
    if ((j->stderr != STDERR_FILENO
            && j->stdout != STDOUT_FILENO
            && j->stdin != STDIN_FILENO ) && io_nb == 1)
    {
        ft_printf("out close\n");
        close(j->stdout);
    }
    if(io_nb == 1)
    {
        ft_printf("out assi\n");
        j->stdout = fd;
    }
    if ((j->stderr != STDERR_FILENO
            && j->stdout != STDOUT_FILENO
            && j->stdin != STDIN_FILENO ) && io_nb == 2)
    {
        ft_printf("err close\n");
        close(j->stderr);
    }
    if(io_nb == 2)
    {
        ft_printf("err assi\n");
        j->stderr = fd;
    }
}
void    io_less(t_ast *ast, t_job *j)
{
    int fd;
    int io_nb;
    t_token   *prev_tok;

    ft_printf("===LESS===\n");
    prev_tok = ast->left->token;
    if ((fd = open(ast_get_lexeme(ast)->lexeme, O_RDONLY, 0644)) < 0)
    {
        access_verification(ast_get_lexeme(ast)->lexeme);
        return ;
    }
    ft_printf("less fd = %d\n", fd);
    if (is_redir_exec(prev_tok->tokind))
        if (ast->left && ast->left->right)
            prev_tok = ast->left->right->token; 
    if (prev_tok->tokind == T_IO_NB)
    {
        io_nb = ft_atoi(prev_tok->lexeme);
        ft_printf("less io = %d\n", io_nb);
        check_opened_fd(j, io_nb, fd);
        return ;
    }
    check_opened_fd(j, 0, fd);
}

void    io_dless(t_ast *ast, t_job *j)
{
    int     fd;
    char    *lex;
    int     io_nb;
    t_token *prev_tok;

    ft_printf("===DLESS===\n");
    prev_tok = ast->left->token;
    lex = generate_random_filename("/tmp/dless_file");
    if ((fd = open(lex, O_CREAT | O_RDWR, 0644)) < 0)
    {
        ft_strdel(&lex);
        g_shell.errorno = ER_UNKNOW;
        return ;
    }
    unlink(lex);
    ft_strdel(&lex);
    lex = ast_get_lexeme(ast)->lexeme;
    write(fd, lex, ft_strlen(lex));
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
    check_opened_fd(j, 0, fd);
}

void    io_lessand(t_ast *ast, t_job *j)
{
    int fd;
    int io_nb;
    t_token   *prev_tok;

    ft_printf("===LESSAND===\n");
    prev_tok = ast->left->token;
    fd = atoi(ast_get_lexeme(ast)->lexeme);
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
    check_opened_fd(j, 0, fd);
}
