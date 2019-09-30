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

int			job_is_stopped(t_job *j)
{
    t_process	*p;

    p = j->first_process;
    while (p)
    {
        if (!p->completed && !p->stopped)
            return (0);
        p = p->next;
    }
    return (1);
}

int			job_is_completed(t_job *j)
{
    t_process	*p;

    p = j->first_process;
    while (p)
    {
        if (!p->completed)
            return (0);
        p = p->next;
    }
    return (1);
}

t_process	*free_process(t_process *p)
{
    t_process *next;

    next = p->next;
    ft_free_tab(p->argv);
    p->argv = NULL;
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
    if (j->stdin != STDIN_FILENO && j->stdin != STDOUT_FILENO && j->stdin != STDERR_FILENO)
        close(j->stdin);
    if (j->stdout != STDIN_FILENO && j->stdout != STDOUT_FILENO && j->stdout != STDERR_FILENO)
        close(j->stdout);
    if (j->stderr != STDIN_FILENO && j->stderr != STDOUT_FILENO && j->stderr != STDERR_FILENO)
        close(j->stderr);
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
