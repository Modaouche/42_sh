/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:57:20 by modaouch          #+#    #+#             */
/*   Updated: 2019/07/04 18:19:03 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "job.h"

t_job	*last_job(void)
{
	t_job	*j;

	j = g_shell.first_job;
	while (j && j->next)
		j = j->next;
	return (j);
}

void	push_back_process(t_process **p, char **envp)
{
	t_process	*new;
	t_process	*tmp;

	tmp = *p;
	if (!(new = (t_process *)ft_memalloc(sizeof(t_process))))
		to_exit(ER_MALLOC);
	if (!tmp)
		*p = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	new->envp = get_env(envp);
}

t_job			*get_job_by_id(unsigned int id)
{
	t_job *j;

	if (id == 0)
		return (NULL);
	j = g_shell.first_job;
	while (j)
	{
		if (j->id == id)
			return (j);
		j = j->next;
	}
	return (NULL);
}

unsigned int	create_job_id(unsigned int start)
{
	unsigned int	id;
	t_job			*j;

	id = start;
	j = g_shell.first_job;
	while (j && id != 0)
	{
		if (j->id == start)
			return (create_job_id(id + 1));
		j = j->next;
	}
	return (id);
}
