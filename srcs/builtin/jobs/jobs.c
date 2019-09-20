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

int		ft_fg(char **args)
{
	(void)args;
	t_job *j;

	j = g_shell.first_job;
	while (j)
	{
		if (!job_is_completed(j))
		{
			continue_job(j, 0);
			break ;
		}
		j = j->next;
	}
	return (0);
}

int		ft_bg(char **args)
{
	(void)args;
	t_job *j;

	j = g_shell.first_job;
	while (j)
	{
		if (!job_is_completed(j))
		{
			continue_job(j, 1);
			break ;
		}
		j = j->next;
	}
	return (0);
}

int		ft_jobs(char **args)
{
	int show_pid;

	show_pid = 0;
	if (args && *args && args[1])
	{
		if (ft_strcmp(args[1], "-l") == 0)
			show_pid = 1;
		else if (ft_strcmp(args[1], "-p") == 0)
			show_pid = 2;
	}
	do_job_notification(show_pid);
	return (0);
}
