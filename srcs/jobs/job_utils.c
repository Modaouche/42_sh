/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:57:20 by modaouch          #+#    #+#             */
/*   Updated: 2019/07/04 18:19:03 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "job.h"

/* Find the active job with the indicated pgid.   useful option "jobs" builtin*/
t_job		*find_job (pid_t pgid)
{
	t_job		*j;

	j = g_shell.first_job;	
	while (j)
	{
		if (j->pgid == pgid)
			return (j);
		j = j->next;
	}
	/*
	for (j = first_job; j; j = j->next)
		if (j->pgid == pgid)
			return j;
	*/
	return (NULL);
}

/* Return true if all processes in the job have stopped or completed.  */
int		job_is_stopped(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed && !p->stopped)
			return (0);
		p = p->next;
	}
	/*
	for (p = j->first_process; p; p = p->next)
		if (!p->completed && !p->stopped)
			return 0;
	*/
	return (1);
}

/* Return true if all processes in the job have completed.  */
int		job_is_completed(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed)
			return (0);
		p = p->next;
	}
	/*
	for (p = j->first_process; p; p = p->next)
		if (!p->completed)
			return 0;
	*/
	return (1);
}

t_process	*free_process(t_process *p)
{
	t_process *next;

	next = p->next;
	ft_free_tab(p->argv);
	ft_memdel((void **)&p);
	return (next);
}

void		free_job(t_job *j)
{
	t_process	*p;

	if (!j)
		return ;
	p = j->first_process;
	while (p)
		p = free_process(p);
	ft_strdel(&(j->command));
	ft_memdel((void **)&j);
}

void		free_jobs(void)
{
	t_job *next;

	while (g_shell.first_job)
	{
		next = g_shell.first_job->next;
		free_job(g_shell.first_job);
		g_shell.first_job = next;
	}
}
