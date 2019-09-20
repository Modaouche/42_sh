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

void	launch_process(t_process *p, pid_t pgid,
		int infile, int outfile, int errfile)
{
	pid_t pid;

	if (g_shell.is_interactive)
	{
		/* Put the process into the process group and give the process group
		   the terminal, if appropriate.
		   This has to be done both by the shell and in the individual
		   child processes because of potential race conditions.  */
		pid = getpid ();
		if (pgid == 0)
			pgid = pid;
		setpgid (pid, pgid);
		if (g_shell.in_fg)
			tcsetpgrp (g_shell.fd, pgid);

		/* Set the handling for job control signals back to the default.  */
		signal_handler(EXEC);
	}

	/* Set the standard input/output channels of the new process.  */
	if (infile != STDIN_FILENO)
	{
		dup2 (infile, STDIN_FILENO);
		close (infile);
	}
	if (outfile != STDOUT_FILENO)
	{
		dup2 (outfile, STDOUT_FILENO);
		close (outfile);
	}
	if (errfile != STDERR_FILENO)
	{
		dup2 (errfile, STDERR_FILENO);
		close (errfile);
	}

	/* Exec the new process.  Make sure we exit.  */
	execve(p->argv[0], p->argv, g_shell.envp);
	perror ("execvp");
	exit (1);
}

void		launch_job (t_job *j)
{
	t_process	*p;
	pid_t	pid;
	int	mypipe[2], infile, outfile;

	infile = j->stdin;
	for (p = j->first_process; p; p = p->next)
	{
		/* Set up pipes, if necessary.  */
		if (p->next)
		{
			if (pipe (mypipe) < 0)
			{
				g_shell.errorno = ER_PIPE;
				return ;
			}				//example : 
			outfile = mypipe[1];		//	process 1   |   process 2
		}
		else					//	in = stdin    	in = pipe[0]
			outfile = j->stdout;		//      out = pipe[1]   out = stdout

		/* Fork the child processes.  */
		pid = fork();
		if (pid == 0)
		{
			/* This is the child process.  */
			(!cmds_verif(p, g_shell.envp)) ? to_exit(g_shell.errorno)\
				: launch_process (p, j->pgid, infile,\
				outfile, j->stderr);
		}
		else if (pid < 0)
		{
			g_shell.errorno = ER_FORK;
			return ;
		}
		else
		{
			/* This is the parent process.  */
			p->pid = pid;
			if (g_shell.is_interactive)
			{
				if (!j->pgid)
					j->pgid = pid;
				setpgid (pid, j->pgid);
			}
		}

		/* Clean up after pipes.  */
		if (infile != j->stdin)
			close (infile);
		if (outfile != j->stdout)
			close (outfile);
		infile = mypipe[0];
	}

	if (!g_shell.is_interactive)
		wait_for_job (j);
	else if (g_shell.in_fg)
		put_job_in_foreground (j, 0);
	else
	{
		format_job_info(j, "launched", 1, 0);
		j->started_in_bg = 1;
		put_job_in_background (j, 0);
	}
	g_shell.in_fg = true;
}

