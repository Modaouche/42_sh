/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 02:39:51 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 07:20:53 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_H
# define JOB_H

# include "shell.h"

/*
** A process is a single process.
**
**	next = next process in pipeline
**	argv =  for exec
**	pid =  process ID
**	completed = true if process has completed
**	sopped =  true if process has stopped
**	status = reported status value
*/

typedef struct		s_p
{
	struct s_p		*next;
	char			**argv;
	char			**envp;
	pid_t			pid;
	bool			completed;
	bool			stopped;
	int				status;
}					t_process;

/*
** A job is a pipeline of processes.
**
**	next = next active job
**	command =  command line, used for messages
**	first_process =  list of processes in this job
**	pgid =  process group ID
**	notified = true if user told about stopped job
**	started_in_bg
**	tmodes = saved terminal modes
**	stdin = standard input channels (useful for redir)
**	stdout = standard output channels (useful for redir)
**	stderr = standard error channels (useful for redir)
**	id
*/
typedef struct		s_job
{
	struct s_job	*next;
	char			*command;
	t_process		*first_process;
	pid_t			pgid;
	bool			notified;
	bool			started_in_bg;
	struct termios	tmodes;
	int				stdin;
	int				stdout;
	int				stderr;
	unsigned int	id;
}					t_job;

typedef struct		s_launch_job
{
	t_process		*p;
	pid_t			pid;
	int				mypipe[2];
	int				infile;
	int				outfile;
}					t_launch_job;

typedef void		(*t_redir_tab)(t_ast *ast, t_job *j);

extern t_redir_tab	g_redir_tab[21];

/*
** The active jobs are linked into a list.  This is its head.
** Put it in my shell globale
*/

t_job				*get_job_by_id(unsigned int id);
int					job_is_stopped(t_job *j);
int					job_is_completed(t_job *j);
t_process			*free_process(t_process *p);
void				free_job(t_job *j);
void				free_jobs(void);
t_job				*last_job(void);
void				put_job_in_foreground(t_job *j, int cont);
void				put_job_in_background(t_job *j, int cont);
void				mark_job_as_running(t_job *j);
void				continue_job(t_job *j, int foreground);
void				launch_process(t_launch_job *lj, pid_t pid,\
					char **env, int errfile);
void				launch_job (t_job *j);
int					mark_process_status (pid_t pid, int status);
void				update_status (void);
void				wait_for_job (t_job *j);
void				format_job_info (t_job *j, const char *status,
					int showpid, int showid);
bool				do_job_notif(t_job *j, int showpid, int update_stat);
void				do_jobs_notif(int showpid);
t_job				*create_job(t_job *j, t_ast *ast);
t_job				*add_job(t_job *j, t_ast *ast);
unsigned int		create_job_id(unsigned int start);
void				push_back_job(t_ast *ast);
void				push_back_process(t_process **p, char **envp);
void				remove_completed_job(t_job **job);
char				*arg_join(char *s1, char *s2, char *s3);

/*
** Redirections functions
*/

t_token				*ast_get_lexeme(t_ast *ast);
void				check_opened_fd(t_job *j, int btn, int fd);
int					get_redir_fd(char *lex, int check);
void				io_great(t_ast *ast, t_job *j);
void				io_dgreat(t_ast *ast, t_job *j);
void				io_greatand(t_ast *ast, t_job *j);
void				io_lessgreat(t_ast *ast, t_job *j);
void				io_clobber(t_ast *ast, t_job *j);
void				io_less(t_ast *ast, t_job *j);
void				io_dless(t_ast *ast, t_job *j);
void				io_lessand(t_ast *ast, t_job *j);

#endif
