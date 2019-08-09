/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:57:20 by modaouch          #+#    #+#             */
/*   Updated: 2019/07/04 18:19:03 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "jobs.h"

/* Find the active job with the indicated pgid.  */
job		*find_job (pid_t pgid)
{
	job		*j;

	j = shell->first_job;	
	while (j)
	{
		if (j->pgid = pgid)
			return (j);
		j = j->next;
	}
	/*
	for (j = first_job; j; j = j->next)
		if (j->pgid == pgid)
			return j;
	*/
	return NULL;
}

/* Return true if all processes in the job have stopped or completed.  */
int		job_is_stopped(job *j)
{
	process	*p;

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
	return 1;
}

/* Return true if all processes in the job have completed.  */
int		job_is_completed(job *j)
{
	process	*p;

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
	return 1;
}

process		*free_process(process *p)
{
	process *next;

	next = p->next;
	free_tabstr(p->argv);
	ft_bzero(p);
	free(p);
	j = NULL;
	ft_printf("free process next = %p\n", next);//rm
	return (next);
}

void		free_job(job *j)
{
	process *p;

	p = j->first_process;
	while (p)
	{
		p = free_process(&p);
		ft_printf("next = %p\n", next);
		//rm and 2line loop
	}
	ft_strdel(j->command);
	free(j);
	j = NULL;
}
