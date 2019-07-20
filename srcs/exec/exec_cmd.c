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
//#include "proc.h"

bool		access_verification(char *cmd)
{
	struct stat file;

	if (access(cmd, F_OK) == -1)
	{
		g_shell.errorno = ER_NOENT;
		return (false);
	}
	if (access(cmd, F_OK | X_OK) == -1)
	{
		g_shell.errorno = ER_ACCES;
		return (false);
	}
	if ((stat(cmd, &file)) == 0)
		if (S_ISDIR(file.st_mode))
		{
			g_shell.errorno = ER_ISDIR;
			return (false);
		}
	return (true);
}

static bool	cmd_verification(char **envp)
{
	char	*path_var;
	char	**sliced_path;
	char	*to_check;
	int	idx;

	g_shell.errorno = NO_ERROR;
	idx = 0;
	to_check = 0;
	if (!(path_var = find_var(envp, "PATH")))
		return (access_verification(g_shell.buff_cmd[0]));
	if (!(sliced_path = ft_split(&path_var[5], ":")))
		to_exit(1);
	while (sliced_path[idx])
	{
		if (!(to_check = ft_multijoin(3, sliced_path[idx++], "/",\
				g_shell.buff_cmd[0])))
			to_exit(1);
		if (!access(to_check, F_OK | X_OK) && !g_shell.errorno)
		{
			free_tabstr(&sliced_path);
			ft_strdel(&(g_shell.buff_cmd[0]));
			g_shell.buff_cmd[0] = to_check;//bug ?
			return (true);
		}
		ft_strdel(&to_check);
	}
	free_tabstr(&sliced_path);
	return (access_verification(g_shell.buff_cmd[0]));
}

bool		exec_cmd(t_ast *ast)
{
	//t_proc	*proc;
	//pid_t	pid;
	int8_t	ret;

	ft_putendl("                           -- IN EXEC CMD ---");
	g_shell.buff_cmd = get_cmd(ast);
	if ((ret = exec_builtin()) != -1)
		return (ret);
	ft_putendl("                           ~~{ok}~~");
	if (!cmd_verification(g_shell.envp))
	{
		error_msg("./42sh");
		return (false);
	}
	for (int i = 0; g_shell.buff_cmd[i] != NULL ; i++)//rm
		ft_putendl(g_shell.buff_cmd[i]);//rm
	return (true);//rm
	
	/*
	
	g_shell.errorno = NOERROR;
	if ((pid = fork()) == 0)
	{
		if (execve(g_shell.buff_cmd[0],\
				g_shell.buff_cmd, g_shell.envp) == -1)
			g_shell.errorno = ER_EXECVE;
	}
	if (father < 0)
		g_shell.errorno = ER_FORK;
	free_tabstr(g_shell.buff_cmd);
	if (g_shell.errorno)
		to_exit(0);
	signal_handler(EXEC);*/
	//wait vv
	//proc_add(proc, pid, g_shell.in_bg);//in this fct > waitpid(proc->status, proc->pid, WUNTRACED | WNOHANG);
}
