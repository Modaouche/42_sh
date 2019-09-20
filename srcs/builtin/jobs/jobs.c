/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 02:17:36 by kicausse          #+#    #+#             */
/*   Updated: 2019/08/30 12:25:27 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "built_in.h"

uint	parse_args(char **args)
{
	uint id;

	if (args == NULL || *args == NULL || args[1] == NULL)
		return (0);
	if (args[1][0] == '%')
		id = ft_atoui(&args[1][1]);
	else if (ft_strcmp(args[1], "-p") == 0 && args[2] != NULL)
		id = ft_atoui(args[2]);
	else
		id = 0;
	return (id);
}

int		ft_fg(char **args)
{
	t_job *j;
	unsigned int jid;

	jid = parse_args(args);
	j = g_shell.first_job;
	while (j)
	{
		if ((jid == 0 && !job_is_completed(j)) || (jid != 0 && j->id == jid))
		{
			ft_printf("[debug] Continuing job [%s]\n", j->command);
			continue_job(j, 0);
			break ;
		}
		j = j->next;
	}
	return (0);
}

int		ft_bg(char **args)
{
	t_job *j;
	uint jid;

	jid = parse_args(args);
	j = g_shell.first_job;
	while (j)
	{
		if ((jid == 0 && !job_is_completed(j))
			|| (jid != 0 && j->id == jid))
		{
			ft_printf("[debug] Continuing job [%s]\n", j->command);
			continue_job(j, 1);
			break ;
		}
		j = j->next;
	}
	return (0);
}

int		ft_jobs(char **args)
{
	int				show_pid;
	t_job			*j;

	show_pid = 0;
	if (args && *args && args[1])
	{
		if (ft_strcmp(args[1], "-l") == 0)
			show_pid = 1;
		else if (ft_strcmp(args[1], "-p") == 0)
		{
			if (args[2] != NULL
				&& (j = get_job_by_id(ft_atoui(args[2]))) != NULL)
			{
				do_job_notif(j, 2, 1);
				return (0);
			}
			show_pid = 2;
		}
	}
	do_jobs_notif(show_pid);
	return (0);
}

void		do_job_notif(t_job *j, int showpid, int update_stat)
{
	if (update_stat)
		update_status();
	if (job_is_completed(j))
	{
		format_job_info(j, "completed", 0, 0);
		j->started_in_bg = 0;
		remove_completed_job(&g_shell.first_job);
	}
	else if (job_is_stopped(j) && !j->notified)//here
	{
		format_job_info (j, "stopped", showpid, 1);
		j->notified = 1;
	}
	else
	{
		format_job_info (j, "running", showpid, 1);
		j->notified = 0;
	}
}

void		do_jobs_notif(int showpid)
{
	t_job		*j;
	t_job		*next;

	j = g_shell.first_job;
	update_status();
	while (j)
	{
		next = j->next;
		do_job_notif(j, showpid, 0);
		j = next;
	}
}
