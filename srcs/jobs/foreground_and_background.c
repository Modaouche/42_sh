/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_and_background.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:57:20 by modaouch          #+#    #+#             */
/*   Updated: 2019/07/04 18:19:03 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "job.h"

/* Put job j in the foreground.  If cont is nonzero,
   restore the saved terminal modes and send the process group a
   SIGCONT signal to wake it up before we block.  */

void	put_job_in_foreground (t_job *j, int cont)
{
	/* Put the job into the foreground.  */
	tcsetpgrp (g_shell.fd, j->pgid);


	/* Send the job a continue signal, if necessary.  */
	if (cont)
	{
		tcsetattr (g_shell.fd, TCSADRAIN, &j->tmodes);
		if (kill (- j->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
	}


	/* Wait for it to report.  */
	wait_for_job (j);

	/* Put the shell back in the foreground.  */
	tcsetpgrp (g_shell.fd, g_shell.pid);

	/* Restore the shell’s terminal modes.  */
	tcgetattr (g_shell.fd, &(j->tmodes));
	tcsetattr (g_shell.fd, TCSADRAIN, g_shell.termios);
}

/* Put a job in the background.  If the cont argument is true, send
   the process group a SIGCONT signal to wake it up.  */

void	put_job_in_background (t_job *j, int cont)
{
	/* Send the job a continue signal, if necessary.  */
	if (cont)
		if (kill (-j->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
}


/* Mark a stopped job J as being running again.  */

void		mark_job_as_running (t_job *j)
{
	t_process *p;

	for (p = j->first_process; p; p = p->next)
		p->stopped = 0;
	j->notified = 0;
}


/* Continue the job J.   is 'fg or bg'*/

void	continue_job (t_job *j, int foreground)
{
	mark_job_as_running (j);
	if (foreground)
		put_job_in_foreground (j, 1);
	else
		put_job_in_background (j, 1);
}

