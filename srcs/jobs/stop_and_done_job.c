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

int		mark_process_prime(t_process *p, int status, int pid)
{
	p->status = status;
	if (WIFSTOPPED(status))
		p->stopped = 1;
	else
	{
		p->completed = 1;
		if (WIFSIGNALED(status))
			ft_printf_fd(STDERR_FILENO,
					"%d: Terminated by signal %d.\n",
					(int)pid, WTERMSIG(p->status));
	}
	return (0);
}

int		mark_process_status(pid_t pid, int status)
{
	t_job		*j;
	t_process	*p;

	if (pid > 0)
	{
		j = g_shell.first_job;
		while (j)
		{
			p = j->first_process;
			while (p)
			{
				if (p->pid == pid)
					return (mark_process_prime(p, pid, status));
				p = p->next;
			}
			j = j->next;
		}
		ft_printf_fd(STDERR_FILENO, "No child process %d.\n", pid);
		return (-1);
	}
	return (-1);
}

void	update_status(void)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	while (!mark_process_status(pid, status))
	{
		if (pid > 0)
			g_shell.ret = WEXITSTATUS(status);
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	}
	if (pid > 0)
		g_shell.ret = WEXITSTATUS(status);
}

void	wait_for_job(t_job *j)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (!mark_process_status(pid, status)
			&& !job_is_stopped(j)
			&& !job_is_completed(j))
	{
		if (pid > 0)
			g_shell.ret = WEXITSTATUS(status);
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	}
	if (pid > 0)
		g_shell.ret = WEXITSTATUS(status);
}

void	format_job_info(t_job *j, const char *status, int showpid, int showid)
{
	if (showid)
		ft_printf_fd(STDERR_FILENO, "[%d] ", j->id);
	if (showpid && showpid != -1)
		ft_printf_fd(STDERR_FILENO, "%ld%c",
					(long)j->pgid, showpid == 2 ? '\n' : ' ');
	if (showpid != 2)
		ft_printf_fd(STDERR_FILENO, "(%s): %s\n", status, j->command);
}
