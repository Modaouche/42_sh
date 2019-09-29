/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:57:20 by modaouch          #+#    #+#             */
/*   Updated: 2019/07/04 18:19:03 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "job.h"

void		launch_process(t_process *p, pid_t pgid,
		int infile, int outfile, int errfile, char **env)
{
	pid_t pid;

	if (g_shell.is_interactive)
	{
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		setpgid(pid, pgid);
		if (g_shell.in_fg)
			tcsetpgrp (g_shell.fd, pgid);
		signal_handler(EXEC);
	}
	if (infile != STDIN_FILENO)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (outfile != STDOUT_FILENO)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	if (errfile != STDERR_FILENO)
	{
		dup2(errfile, STDERR_FILENO);
		close(errfile);
	}
	(p->argv && !is_builtin(p->argv[0])) ? execve(p->argv[0], p->argv, env)\
		: exit(exec_builtin(p->argv));
	g_shell.errorno = ER_EXECVE;
	error_msg("execvp");
	to_exit(ER_EXECVE);
}

/*  example for pipe : 
**
**  process 1   |   process 2           |           process 3
**  in = stdin    	in = pipe[0]                    in = pipe[0] (another pipe)
**  out = pipe[1]   out = pipe[1] (another pipe)    out = stdout
**	
*/

void		launch_job(t_job *j)
{
	t_process	*p;
	pid_t		pid;
	int			mypipe[2];
	int			infile;
	int			outfile;

	infile = j->stdin;
	p = j->first_process;
	while (p)
	{
		if (p->next)
		{
			if (pipe(mypipe) < 0)
			{
				g_shell.errorno = ER_PIPE;
				return ;
			}
			outfile = mypipe[1];
		}
		else
			outfile = j->stdout;
		pid = fork();
		if (pid == 0)
		{
			(!cmds_verif(p, g_shell.envp)) ? to_exit(g_shell.errorno)\
				: launch_process(p, j->pgid, infile,\
				outfile, j->stderr, p->envp);
		}
		else if (pid < 0)
		{
			g_shell.errorno = ER_FORK;
			return ;
		}
		else
		{
			p->pid = pid;
			if (g_shell.is_interactive)
			{
				if (!j->pgid)
					j->pgid = pid;
				setpgid(pid, j->pgid);
			}
		}
		if (infile != j->stdin)
			close(infile);
		if (outfile != j->stdout)
			close(outfile);
		infile = mypipe[0];
		p = p->next;
	}
	if (!g_shell.is_interactive)
		wait_for_job(j);
	else if (g_shell.in_fg)
		put_job_in_foreground(j, 0);
	else
	{
		format_job_info(j, "launched", 0, 1);
		j->started_in_bg = 1;
		put_job_in_background(j, 0);
	}
	g_shell.in_fg = true;
}
