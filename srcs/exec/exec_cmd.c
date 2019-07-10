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

static bool		cmd_verification(char *first_word, char **envp)
{
	char	*path_var;

	if (!(path_var = get_var_env(envp, "PATH")))//tobuild
		if (!is_without_path_cmd(g_shell.buffer[0]))//tobuild
			return (false);
	//to_finish	
}

bool		exec_cmd(t_ast *ast)
{
	t_proc	*proc;
	pid_t	pid;

	g_shell.buffer_cmd = get_cmd();//to_build
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
	proc_add(proc, pid, g_shell.in_bg);//in this fct > waitpid(proc->status, proc->pid, WUNTRACED | WNOHANG);
}
