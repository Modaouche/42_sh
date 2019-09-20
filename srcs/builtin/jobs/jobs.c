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

int		ft_jobs(char **args)
{
	if (args && *args && ft_strcmp(args[1], "-l") == 0)
		do_job_notification(1);
	else
		do_job_notification(0);
	return (0);
}
