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
#include "jobs.h"

Now let’s consider what actions must be taken by the shell when it launches a job into the foreground, and how this differs from what must be done when a background job is launched.

When a foreground job is launched, the shell must first give it access to the controlling terminal by calling tcsetpgrp. Then, the shell should wait for processes in that process group to terminate or stop. This is discussed in more detail in Stopped and Terminated Jobs.

When all of the processes in the group have either completed or stopped, the shell should regain control of the terminal for its own process group by calling tcsetpgrp again. Since stop signals caused by I/O from a background process or a SUSP character typed by the user are sent to the process group, normally all the processes in the job stop together.

The foreground job may have left the terminal in a strange state, so the shell should restore its own saved terminal modes before continuing. In case the job is merely stopped, the shell should first save the current terminal modes so that it can restore them later if the job is continued. The functions for dealing with terminal modes are tcgetattr and tcsetattr; these are described in Terminal Modes.

Here is the sample shell’s function for doing all of this.

/* Put job j in the foreground.  If cont is nonzero,
   restore the saved terminal modes and send the process group a
   SIGCONT signal to wake it up before we block.  */

void	put_job_in_foreground (job *j, int cont)
{
	/* Put the job into the foreground.  */
	tcsetpgrp (shell_terminal, j->pgid);


	/* Send the job a continue signal, if necessary.  */
	if (cont)
	{
		tcsetattr (shell_terminal, TCSADRAIN, &j->tmodes);
		if (kill (- j->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
	}


	/* Wait for it to report.  */
	wait_for_job (j);

	/* Put the shell back in the foreground.  */
	tcsetpgrp (shell_terminal, shell_pgid);

	/* Restore the shell’s terminal modes.  */
	tcgetattr (shell_terminal, &j->tmodes);
	tcsetattr (shell_terminal, TCSADRAIN, &shell_tmodes);
}

If the process group is launched as a background job, the shell should remain in the foreground itself and continue to read commands from the terminal.

In the sample shell, there is not much that needs to be done to put a job into the background. Here is the function it uses:

/* Put a job in the background.  If the cont argument is true, send
   the process group a SIGCONT signal to wake it up.  */

void	put_job_in_background (job *j, int cont)
{
	/* Send the job a continue signal, if necessary.  */
	if (cont)
		if (kill (-j->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
}


The shell can continue a stopped job by sending a SIGCONT signal to its process group. If the job is being continued in the foreground, the shell should first invoke tcsetpgrp to give the job access to the terminal, and restore the saved terminal settings. After continuing a job in the foreground, the shell should wait for the job to stop or complete, as if the job had just been launched in the foreground.

The sample shell program handles both newly created and continued jobs with the same pair of functions, put_job_in_foreground and put_job_in_background. The definitions of these functions were given in Foreground and Background. When continuing a stopped job, a nonzero value is passed as the cont argument to ensure that the SIGCONT signal is sent and the terminal modes reset, as appropriate.

This leaves only a function for updating the shell’s internal bookkeeping about the job being continued:

/* Mark a stopped job J as being running again.  */

void
mark_job_as_running (job *j)
{
  Process *p;

  for (p = j->first_process; p; p = p->next)
    p->stopped = 0;
  j->notified = 0;
}


/* Continue the job J.  */

void
continue_job (job *j, int foreground)
{
  mark_job_as_running (j);
  if (foreground)
    put_job_in_foreground (j, 1);
  else
    put_job_in_background (j, 1);
}

