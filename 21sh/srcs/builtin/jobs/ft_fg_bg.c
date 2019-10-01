/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg_bg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 08:21:14 by araout            #+#    #+#             */
/*   Updated: 2019/09/23 08:23:26 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "built_in.h"

int		ft_fg(char **args)
{
	t_job			*j;
	unsigned int	jid;

	jid = parse_args(args);
	j = g_shell.first_job;
	while (j)
	{
		if ((jid == 0 && !job_is_completed(j)) || (jid != 0 && j->id == jid))
		{
			continue_job(j, 1);
			return (0);
		}
		j = j->next;
	}
	ft_putendl_fd("fg: no current job", STDERR_FILENO);
	return (1);
}

int		ft_bg(char **args)
{
	t_job		*j;
	uint		jid;

	jid = parse_args(args);
	j = g_shell.first_job;
	while (j)
	{
		if ((jid == 0 && !job_is_completed(j) && job_is_stopped(j))
			|| (jid != 0 && j->id == jid))
		{
			if (jid != 0 && !job_is_stopped(j))
			{
				ft_putendl_fd("bg: job already in background", STDERR_FILENO);
				return (1);
			}
			continue_job(j, 0);
			return (0);
		}
		j = j->next;
	}
	ft_putendl_fd("bg: no current job", STDERR_FILENO);
	return (1);
}
