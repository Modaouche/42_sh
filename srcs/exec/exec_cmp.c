/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:57:20 by modaouch          #+#    #+#             */
/*   Updated: 2019/07/04 18:19:03 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool		is_slice_exec(t_tok tokind)
{
	if (tokind == T_AMPER)
		g_shell.in_fg = false;
	else if (token_cmp(tokind, T_SEMI, T_NEWL, T_EOF, -1))
		g_shell.in_fg = true;
	if (token_cmp(tokind, T_SEMI, T_AMPER, T_NEWL, T_EOF, -1))
		return (true);
	return (false);
}

bool		is_and_or_exec(t_tok tokind)
{
	if (token_cmp(tokind, T_AND_IF, T_OR_IF, -1))
		return (true);
	return (false);
}

bool		is_redir_exec(t_tok tokind)
{
	if (token_cmp(tokind, T_GREAT, T_GREATAND, T_DGREAT,\
			T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS,\
			T_LESSAND, T_DLESSDASH, -1))
		return (true);
	return (false);
}

bool		is_other_exec(t_tok tokind)
{
	if (!is_slice_exec(tokind) && !is_and_or_exec(tokind)\
		&& !is_redir_exec(tokind) && tokind != T_PIPE)
		return (true);
	return (false);
}

bool		ft_strcmp_ret(char *to_cmp, char *with, bool ret)
{
	if (!ft_strcmp(to_cmp, with) && ret == 0)
		return (true);
	return (ret);
}
