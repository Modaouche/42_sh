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

char    *ast_get_lexeme();//to build

void    io_great(t_ast ast, t_job *j)
{
    int fd;

    if (fd = open(ast_get_lexeme(    ), O_CREAT | O_TRUNC | O_WRONLY, 0644))
    {
        access_verification(ast_get_lexeme(    ));
        return ;
    }
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

void    io_dgreat(t_ast ast, t_job *j)
{
    int fd;

    if (fd = open(ast_get_lexeme(    ), O_CREAT | O_TRUNC | O_WRONLY, 0644))
    {
        access_verification(ast_get_lexeme(    ));
        return ;
    }
    lseek(fd, 0, SEEK_END);
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

void    io_greatand(t_ast ast, t_job *j)
{
    int fd;

    fd = atoi(ast_get_lexeme(   ));
    //if (access_verification(ast_get_lexeme(    )))
    //  return ;  
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

void    io_lessgreat(t_ast ast, t_job *j)
{
        //Bonus to do
}

void    io_clobber(t_ast ast, t_job *j)
{

        //Bonus to do
}
