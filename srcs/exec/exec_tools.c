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

static int 	ft_putendlr(char *s)
{
	ft_putendl(s);
	return (0);
}

ssize_t			exec_builtin(void)
{
	char		**cmd;
	int8_t		ret;

	ret = -1;
	cmd = g_shell.buff_cmd;
	(!ft_strcmp("set", cmd[0]) && ret == -1) ? ret = ft_putendlr("is builtin") : 0;//ret = ret_set(cmd) : 0;//tobuild VV
	(!ft_strcmp("unset", cmd[0]) && ret == -1) ? ret = ft_putendlr("is builtin") : 0;//ret = ret_unset(cmd) : 0;
	(!ft_strcmp("cd", cmd[0]) && ret == -1) ? ret = ft_putendlr("is builtin") : 0;//ret = ret_cd(cmd) : 0;
	(!ft_strcmp("echo", cmd[0]) && ret == -1) ? ret = ft_putendlr("is builtin") : 0;//ret = ret_echo(cmd) : 0;
	(!ft_strcmp("exit", cmd[0]) && ret == -1) ? ret = ft_putendlr("is builtin") : 0;//ret = ret_exit(cmd) : 0;
	(!ft_strcmp("jobs", cmd[0]) && ret == -1) ? ret = ft_putendlr("is builtin") : 0;//ret = ret_jobs(cmd) : 0;
	(!ft_strcmp("fg", cmd[0]) && ret == -1) ? ret = ft_putendlr("is builtin") : 0;//ret = ret_fg(cmd) : 0;
	(!ft_strcmp("bg", cmd[0]) && ret == -1) ? ret = ft_putendlr("is builtin") : 0;//ret = ret_bg(cmd) : 0;//until here
	return (ret);//-1, false ou true
}

char			**get_cmd(t_ast *ast)
{
	char		**cmd;
	t_ast		*tmptr;
	ssize_t		len;

	tmptr = ast;
	len = 0;
	if (g_shell.buff_cmd)
		free_tabstr(&(g_shell.buff_cmd));
	while (tmptr)
	{
		if (is_other_exec(tmptr->token->tokind))
			len++;
		tmptr = tmptr->left;
	}
	if (!(cmd = (char **)malloc(sizeof(char *) * (len + 1))))
		to_exit(ER_MALLOC);
	cmd[len--] = NULL;
	tmptr = ast;
	while (tmptr && len >= 0)
	{
		if (is_other_exec(tmptr->token->tokind))
			if (!(cmd[len--] = ft_strdup(tmptr->token->lexeme)))
				to_exit(ER_MALLOC);
		tmptr = tmptr->left;
	}
	return (cmd);
}
