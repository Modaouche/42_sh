/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:57:20 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 10:54:33 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/wait.h>
#include "job.h"

bool		access_verification(char *cmd)
{
	struct stat		file;

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
	t_cmd_verif_prime s;

	g_shell.errorno = NO_ERROR;
	s.idx = 0;
	s.to_check = 0;
	if (!(s.path_var = find_var(envp, "PATH")))
		return (access_verification(argv[0]));
	if (!(s.sliced_path = ft_split(&(s.path_var[5]), ":")))
		to_exit(1);
	while (s.sliced_path[s.idx])
	{
		if (!(s.to_check = ft_multijoin(3, s.sliced_path[s.idx++], "/",\
				argv[0])))
			to_exit(1);
		if (!access(s.to_check, F_OK | X_OK) && !g_shell.errorno)
		{
			ft_free_tab(s.sliced_path);
			ft_strdel(&(argv[0]));
			argv[0] = s.to_check;
			return (true);
		}
		ft_strdel(&(s.to_check));
	}
	ft_free_tab(s.sliced_path);
	return (access_verification(argv[0]));
}

bool		cmds_verif(t_process *p, char **envp)
{
	if (p->argv && !is_builtin(p->argv[0])
		&& cmd_verif_prime(envp, p->argv) == false)
		return (false);
	return (true);
}
