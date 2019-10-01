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

void		launch_process(t_launch_job *lj, pid_t pgid, char **env,
			int errfile)
{
	pid_t pid;

	if (g_shell.is_interactive)
	{
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		setpgid(pid, pgid);
		if (g_shell.in_fg)
			tcsetpgrp(g_shell.fd, pgid);
		signal_handler(EXEC);
	}
	if (lj->infile != STDIN_FILENO)
		dup2(lj->infile, STDIN_FILENO);
	if (lj->outfile != STDOUT_FILENO)
		dup2(lj->outfile, STDOUT_FILENO);
	if (errfile != STDERR_FILENO)
		dup2(errfile, STDERR_FILENO);
	(lj->p->argv && !is_builtin(lj->p->argv[0])) ?
		execve(lj->p->argv[0], lj->p->argv, env)\
		: exit(exec_builtin(tabdup(lj->p->argv)));
	g_shell.errorno = ER_EXECVE;
	error_msg("execvp");
	to_exit(ER_EXECVE);
}

void		process_fork_dfg(t_launch_job *lj, t_job *j)
{
	if (lj->pid == 0)
	{
		(!cmds_verif(lj->p, g_shell.envp)) ? to_exit(g_shell.errorno)\
			: launch_process(lj, j->pgid, lj->p->envp, j->stderr);
	}
	else if (lj->pid < 0)
	{
		g_shell.errorno = ER_FORK;
		return ;
	}
	else
	{
		lj->p->pid = lj->pid;
		if (g_shell.is_interactive)
		{
			if (!j->pgid)
				j->pgid = lj->pid;
			setpgid(lj->pid, j->pgid);
		}
	}
	if (lj->infile != j->stdin)
		close(lj->infile);
	if (lj->outfile != j->stdout)
		close(lj->outfile);
	lj->infile = lj->mypipe[0];
}

void		save_job_dfg(t_job *j)
{
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

void		launch_job(t_job *j)
{
	t_launch_job lj;

	lj.infile = j->stdin;
	lj.p = j->first_process;
	while (lj.p)
	{
		if (lj.p->next)
		{
			if (pipe(lj.mypipe) < 0)
			{
				g_shell.errorno = ER_PIPE;
				return ;
			}
			lj.outfile = lj.mypipe[1];
		}
		else
			lj.outfile = j->stdout;
		lj.pid = fork();
		process_fork_dfg(&lj, j);
		lj.p = lj.p->next;
	}
	save_job_dfg(j);
}
