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


/* A process is a single process.  */
typedef struct		s_p
{
	struct s_p	*next;		/* next process in pipeline */
	char		**argv;		/* for exec */
	pid_t		pid;		/* process ID */
	bool		completed;	/* true if process has completed */
	bool		stopped;	/* true if process has stopped */
	int		status;		/* reported status value */
}			t_process;


/* A job is a pipeline of processes.  */
typedef struct		s_job
{
	struct s_job	*next;		/* next active job */
	char		*command;	/* command line, used for messages */
	t_process	*first_process;	/* list of processes in this job */
	pid_t		pgid;		/* process group ID */
	bool		notified;	/* true if user told about stopped job */
	bool		started_in_bg;
	struct termios	tmodes;		/* saved terminal modes */
	int		stdin;		/* standard input channels (useful for redir)*/
	int		stdout;		/* standard output channels (useful for redir)*/
	int		stderr;		/* standard error channels (useful for redir)*/
}			t_job;

/* The active jobs are linked into a list.  This is its head. 
 * Put it in my shell globale */

t_job			*find_job (pid_t pgid);
int			job_is_stopped(t_job *j);
int			job_is_completed(t_job *j);
t_process		*free_process(t_process *p);
void			free_job(t_job *j);
void			free_jobs(void);
t_job			*last_job(void);
void			put_job_in_foreground(t_job *j, int cont);
void			put_job_in_background(t_job *j, int cont);
void			mark_job_as_running(t_job *j);
void			continue_job(t_job *j, int foreground);
void			launch_process(t_process *p, pid_t pid,\
				int , int , int );
void			launch_job (t_job *j);
int			mark_process_status (pid_t pid, int status);
void			update_status (void);
void			wait_for_job (t_job *j);
void			format_job_info (t_job *j, const char *status,
				int showpid);
void			do_job_notification (int showpid);
t_job			*create_job(t_job *j, t_ast *ast);
t_job			*add_job(t_job *j, t_ast *ast);
void			push_back_job(t_ast *ast);
void			push_back_process(t_process **p);
void			remove_completed_job(t_job **job);
#endif
