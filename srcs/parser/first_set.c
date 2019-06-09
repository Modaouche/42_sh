/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 06:59:16 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 11:25:11 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "shell.h"

int	first_set(int kind, ...)//name tochange maybe in nextok
{
    va_list tokens;
    int current_token;

    va_start(tokens, kind);
    while ((current_token = va_arg(tokens, int)) != -1)
    {
        if (current_token == kind)
        {
            va_end(tokens);
            return (1);
        }
    }
    va_end(tokens);
    return (0);
}

int	head_of_line(t_ast *ast)
{
	if (!ast)
		return (-2);
	if (ast->right)
		return (head_of_line(ast->right));	
	if (!ast->right)
		return (ast->token->tokind);
	return (-2);
}
