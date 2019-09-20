/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_and_done_job.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:57:20 by modaouch          #+#    #+#             */
/*   Updated: 2019/07/04 18:19:03 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "job.h"

/* Store the status of the process pid that was returned by waitpid.
   Return 0 if all went well, nonzero otherwise.  */

int	mark_process_status (pid_t pid, int status)
{
	t_job *j;
	t_process *p;


	if (pid > 0)
	{
		/* Update the record for the process.  */
		for (j = g_shell.first_job; j; j = j->next)
			for (p = j->first_process; p; p = p->next)
				if (p->pid == pid)
				{
					p->status = status;
					if (WIFSTOPPED (status))
						p->stopped = 1;
					else
					{
						p->completed = 1;
						if (WIFSIGNALED (status))
							fprintf(stderr, "%d: Terminated by signal %d.\n",
								(int) pid, WTERMSIG (p->status));
					}
					return 0;
				}
		fprintf (stderr, "No child process %d.\n", pid);
		return -1;
	}
	return -1;
}


/* Check for processes that have status information available,
   without blocking.  */

void		update_status (void)
{
	int	status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	while (!mark_process_status (pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
}


/* Check for processes that have status information available,
   blocking until all processes in the given job have reported.  */

void		wait_for_job (t_job *j)
{
	int status;
	pid_t pid;

	ft_printf("command : %s\n" , j->command);
	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	ft_printf("pid : %d\n" , pid);
	while (!mark_process_status(pid, status)
			&& !job_is_stopped(j)
			&& !job_is_completed(j))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);

	/*do
		pid = waitpid (WAIT_ANY, &status, WUNTRACED);
	while (!mark_process_status (pid, status)
			&& !job_is_stopped (j)
			&& !job_is_completed (j));
	*/
}

/* Format information about job status for the user to look at.  */

void	format_job_info(t_job *j, const char *status, int showpid, int showid)
{
	if (showid)
		ft_printf_fd(STDERR_FILENO, "[%d] ", j->id);
	if (showpid && showpid != -1)
		ft_printf_fd(STDERR_FILENO, "%ld%c", (long)j->pgid, showpid == 2 ? '\n' : ' ');
	if (showpid != 2)
		ft_printf_fd(STDERR_FILENO, "(%s): %s\n", status, j->command);
}
