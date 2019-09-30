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


void    check_opened_fd(t_job *j, int btn, int fd)
{
    if (j->stdin != STDIN_FILENO && btn == 0)
        close(j->stdin);
    if(btn == 0)
        j->stdin = fd;

    if (j->stdout != STDOUT_FILENO && btn == 1)
        close(j->stdout);
    if(btn == 1)
        j->stdout = fd;

    if (j->stderr != STDERR_FILENO && btn == 2)
        close(j->stderr);
    if(btn == 2)
        j->stderr = fd;
}

void    io_less(t_ast *ast, t_job *j)
{
    int fd;
    int io_nb;

    ft_printf("===LESS===\n");
    if ((fd = open(ast_get_lexeme(ast), O_CREAT | O_WRONLY, 0644)) < 0)
    {
        access_verification(ast_get_lexeme(ast));
        return ;
    }
    if (ast->left->token->tokind == T_IO_NB)
    {
        io_nb = ft_atoi(ast->left->token->lexeme);
        check_opened_fd(j, io_nb, fd);
        return ;
    }
    check_opened_fd(j, 0, fd);
}

void    io_dless(t_ast *ast, t_job *j)
{
    int     fd;
    char    *lex;
    int io_nb;

    ft_printf("===DLESS===\n");
    lex = generate_random_filename("/tmp/dless_file");
    if ((fd = open(lex, O_CREAT | O_RDWR, 0644)) < 0)
    {
        ft_strdel(&lex);
        g_shell.errorno = ER_UNKNOW;
        return ;
    }
    unlink(lex);
    ft_strdel(&lex);
    lex = ast_get_lexeme(ast);
    write(fd, lex, ft_strlen(lex));
    if (ast->left->token->tokind == T_IO_NB)
    {
        io_nb = ft_atoi(ast->left->token->lexeme);
        check_opened_fd(j, io_nb, fd);
        return ;
    }
    check_opened_fd(j, 0, fd);
}

void    io_lessand(t_ast *ast, t_job *j)
{
    int fd;
    int io_nb;

    ft_printf("===LESSAND===\n");
    fd = atoi(ast_get_lexeme(ast));
    if (ast->left->token->tokind == T_IO_NB)
    {
        io_nb = ft_atoi(ast->left->token->lexeme);
        check_opened_fd(j, io_nb, fd);
        return ;
    }
    check_opened_fd(j, 0, fd);
}
