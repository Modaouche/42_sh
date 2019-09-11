/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:57:20 by modaouch          #+#    #+#             */
/*   Updated: 2019/07/04 18:19:03 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			*find_var(char **envp, char *with)//to_add in env fct or check if araout created it
{
	int		idx;
	char		*to_cmp;
	uint64_t	len;

	idx = -1;
	while (envp[++idx])
	{
		len = ((len = (uint64_t)ft_strchr(envp[idx], '=')))\
		      ? len - (uint64_t)envp[idx] : 0;
		to_cmp = ft_strndup(envp[idx], len);
		if (!ft_strcmp(to_cmp, with))
			return (envp[idx]);
		ft_strdel(&to_cmp);
	}
	return (0);
}

char			**get_cmd(t_ast *ast)
{
	char		**cmd;
	t_ast		*tmptr;
	ssize_t		len;

	tmptr = ast;
	len = 0;
	while (tmptr)
	{
		if (tmptr->token->tokind == T_WORD)
			len++;
		tmptr = tmptr->left;
	}
	if (!(cmd = (char **)malloc(sizeof(char *) * (len + 1))))
		to_exit(ER_MALLOC);
	cmd[len--] = NULL;
	tmptr = ast;
	while (tmptr && len >= 0)
	{
		if (tmptr->token->tokind == T_WORD)
			if (!(cmd[len--] = ft_strdup(tmptr->token->lexeme)))
				to_exit(ER_MALLOC);
		tmptr = tmptr->left;
	}
	return (cmd);
}
