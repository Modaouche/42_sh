/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:57:20 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 11:48:30 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			*find_var(char **envp, char *with)
{
	int			idx;
	char		*to_cmp;
	uint64_t	len;
	uint64_t	tmp;

	idx = -1;
	while (envp[++idx])
	{
		tmp = (uint64_t)ft_strchr(envp[idx], '=');
		len = tmp;
		len = (tmp) ? len - (uint64_t)envp[idx] : 0;
		to_cmp = ft_strndup(envp[idx], len);
		if (!ft_strcmp(to_cmp, with))
			return (envp[idx]);
		ft_strdel(&to_cmp);
	}
	return (0);
}

char			**get_assignments(t_ast *ast)
{
	char		**cmd;
	t_ast		*tmptr;
	ssize_t		len;

	tmptr = ast;
	len = 0;
	while (tmptr)
	{
		if (tmptr->token->tokind == T_ASGMT_WRD)
			len++;
		if (tmptr->token->tokind == T_ASGMT_WRD)
			ft_printf("ASSIGN [%d] [%s]\n", len, tmptr->token->lexeme);
		else if (tmptr->token->tokind == T_WORD)
			ft_printf("WORD [%d] [%s]\n", len, tmptr->token->lexeme);
		tmptr = tmptr->left;
	}
	if (!len)
		return (NULL);
	if (!(cmd = (char **)malloc(sizeof(char *) * (len + 1))))
		to_exit(ER_MALLOC);
	cmd[len--] = NULL;
	tmptr = ast;
	while (tmptr && len >= 0)
	{
		if (tmptr->token->tokind == T_ASGMT_WRD
			&& !(cmd[len--] = ft_strdup(tmptr->token->lexeme)))
			to_exit(ER_MALLOC);
		tmptr = tmptr->left;
	}
	return (cmd);
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
		if (tmptr->token->tokind == T_WORD
			&& !(cmd[len--] = ft_strdup(tmptr->token->lexeme)))
			to_exit(ER_MALLOC);
		tmptr = tmptr->left;
	}
	return (cmd);
}
