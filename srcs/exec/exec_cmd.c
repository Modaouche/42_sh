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
#include "job.h"

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

bool		cmds_verif(t_process *p, char **envp)
{
	if (!is_builtin(0, p->argv[0]) && cmd_verif_prime(envp, p->argv) == false)
		return (false);
	return (true);
}

bool		exec_cmd(t_ast *ast, bool is_redir_pipe) 
{
	ft_putendl(" -- IN EXEC CMD ---");
	if (!is_redir_pipe && is_builtin(ast, 0))
		return (exec_builtin(ast));
	push_back_job(ast);
	g_shell.errorno = NO_ERROR;
	launch_job(last_job());
	if (g_shell.errorno)
	{
		remove_last_job(&g_shell.first_job);
		error_msg("./42sh");
	}
	return (g_shell.errorno ? 0 : 1);
}
