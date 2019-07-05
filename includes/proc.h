/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 02:39:51 by modaouch          #+#    #+#             */
/*   Updated: 2019/07/04 02:55:07 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROC_H
# define PROC_H

# include "shell.h" //some includes...

typedef struct	s_ps
{
	char	*name;
	pid_t	pid;
	pid_t	pgrp;
	t_bool	mode;
	t_proc *next;
}		t_ps;

t_ps		*ps_create(some_stuffs);
void		ps_add(...);
void		ps_del();
t_ps		*get_ps();

#endif
