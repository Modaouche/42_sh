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
#include "proc.h"

bool		acces_verification(char *cmd)
{
	return (false);
}

static bool		cmd_verification(char *first_word, char **envp)
{
	char	*path_var;
	char	**sliced_path;
	char	*to_check;
	int	idx;

	g_shell.error_no = 0;
	idx = 0;
	to_check = 0;
	if (!(path_var = find_var(envp, "PATH")))//tobuild
		return (acces_verification(g_shell.buffer[0]) ? true : false);//check if i need to malloc //!\\//
	sliced_path = ft_strsplit(&path_var[5], ':');
	while (sliced_path[idx])
	{
		ft_multijoin(3, to_check, "/", first_word);
	}
}

bool		exec_cmd(t_ast *ast)
{
	t_proc	*proc;
	pid_t	pid;

	g_shell.buffer_cmd = get_cmd(ast);//to_build
	if (cmd_verification(g_shell.buffer_cmd[0], g_shell.envp))//tofinish
		return (false);
	if ((pid = fork()) == 0)
	{
		if (execve(g_shell.buffer_cmd[0],\
				g_shell.buffer_cmd, g_shell.envp) == -1)
			exit_shell("execve", g_shell.buffer_cmd[0]);//tobuild
	}
	else if (father < 0)
		exit_shell("fork");
	signal_handler(EXEC);
	//proc_add(proc, pid, g_shell.in_bg);//in this fct > waitpid(proc->status, proc->pid, WUNTRACED | WNOHANG);
}
