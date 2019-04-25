/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_5_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 00:02:18 by modaouch          #+#    #+#             */
/*   Updated: 2019/04/07 00:38:27 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void        command_fct(t_ast **ast, t_edit *line_e)
{
    //ft_printf("--<command_fct>--\n");
    if (first_set(head_of_line(*ast), T_WORD, -1))
        ast_insert_left(get_next_token(&(line_e->line), &(line_e->i)), ast);
    //ft_printf("cmdfct|%d|\n", head_of_line(*ast));
}

void        cmd_suffix_fct()
{
    
}

void        cmd_suffix_opt_fct()
{
    
}
