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
#include <sys/wait.h>
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

static bool	cmd_verif_prime(char **envp, char **argv)
{
	char	*path_var;
	char	**sliced_path;
	char	*to_check;
	int	idx;

	g_shell.errorno = NO_ERROR;
	idx = 0;
	to_check = 0;
	if (!(path_var = find_var(envp, "PATH")))
		return (access_verification(argv[0]));
	if (!(sliced_path = ft_split(&path_var[5], ":")))
		to_exit(1);
	while (sliced_path[idx])
	{
		if (!(to_check = ft_multijoin(3, sliced_path[idx++], "/",\
				argv[0])))
			to_exit(1);
		if (!access(to_check, F_OK | X_OK) && !g_shell.errorno)
		{
			free_tabstr(&sliced_path);
			ft_strdel(&(argv[0]));
			argv[0] = to_check;
			return (true);
		}
		ft_strdel(&to_check);
	}
	free_tabstr(&sliced_path);
	return (access_verification(argv[0]));
}

bool		cmds_verif(char **envp)
{
	t_job		*j;
	t_process	*p;

	j = last_job();
	p = j->first_process;
	while (p->next)
	{
		if (!is_builtin(p->argv[0]) && cmd_verif_prime(envp, p->argv) == false)
			return (false);
		p = p->next;
	}
	return (true);
}

bool		exec_cmd(t_ast *ast, bool is_redir_pipe) 
{
	ft_putendl(" -- IN EXEC CMD ---");
	if (!is_redir_pipe && is_builtin(ast))
		return (exec_builtin(ast));
	if (!is_redir_pipe)
		push_back_job(ast);
	if (!cmds_verif(g_shell.envp))
	{
		error_msg("./42sh");
		return (false);
	}
	g_shell.errorno = NO_ERROR;
	launch_job(last_job(g_shell.first_job));
	if (g_shell.errorno)
	{
		free_job(last_job());
		error_msg();
	}
	return (g_shell.errorno ? 0 : 1);
	/*
	if ((pid = fork()) == 0)
	{
		signal_handler(EXEC);
		if (execve(g_shell.buff_cmd[0],\
				g_shell.buff_cmd, g_shell.envp) == -1)
			g_shell.errorno = ER_EXECVE;
	}
	if (pid < 0)
		g_shell.errorno = ER_FORK;
	free_tabstr(&g_shell.buff_cmd);
	if (g_shell.errorno)
		to_exit(0);
	signal_handler(REGULAR);
	waitpid(WAIT_ANY, &status, WUNTRACED);
	return (g_shell.errorno ? 0 : 1);
*/
}
