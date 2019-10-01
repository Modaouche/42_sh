/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_and_background.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:57:20 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 08:54:33 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "job.h"

void	put_job_in_foreground(t_job *j, int cont)
{
	tcsetpgrp(g_shell.fd, j->pgid);
	if (cont)
	{
		tcsetattr(g_shell.fd, TCSADRAIN, &j->tmodes);
		if (kill(-(j->pgid), SIGCONT) < 0)
			ft_printf_fd(2, "42sh: kill (SIGCONT) error\n");
	}
	wait_for_job(j);
	tcsetpgrp(g_shell.fd, g_shell.pid);
	tcgetattr(g_shell.fd, &(j->tmodes));
	tcsetattr(g_shell.fd, TCSADRAIN, g_shell.termiold);
}

void	put_job_in_background(t_job *j, int cont)
{
	if (cont)
		if (kill(-j->pgid, SIGCONT) < 0)
			ft_printf_fd(2, "42sh: kill (SIGCONT) error\n");
}

void	mark_job_as_running(t_job *j)
{
	t_process *p;

	p = j->first_process;
	while (p != NULL)
	{
		p->stopped = 0;
		p = p->next;
	}
	j->notified = 0;
}

void	continue_job(t_job *j, int foreground)
{
	mark_job_as_running(j);
	if (foreground)
		put_job_in_foreground(j, 1);
	else
		put_job_in_background(j, 1);
}
