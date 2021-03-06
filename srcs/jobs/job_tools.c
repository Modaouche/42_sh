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
#include "job.h"

static bool	g_is_pipe;

static void		realloc_argv(t_process **process, char *to_add)
{
	char		**new;
	int			len;
	t_process	*p;

	p = *process;
	while (p && p->next)
		p = p->next;
	len = ft_tablen(p->argv);
	if (!(new = (char **)ft_memalloc(sizeof(char *) * (len + 2))))
		to_exit(ER_MALLOC);
	len = 0;
	while (p->argv && p->argv[len])
	{
		new[len] = p->argv[len];
		len++;
	}
	if (!(new[len++] = ft_strdup(to_add)))
		to_exit(ER_MALLOC);
	new[len] = NULL;
	ft_memdel((void **)&(p->argv));
	p->argv = new;
}

static void		realloc_assign(t_process **process, char *to_add)
{
	char		**new;
	int			len;
	t_process	*p;

	p = *process;
	while (p && p->next)
		p = p->next;
	len = ft_tablen(p->envp);
	if (!(new = (char **)ft_memalloc(sizeof(char *) * (len + 2))))
		to_exit(ER_MALLOC);
	len = 0;
	while (p->envp && p->envp[len])
	{
		new[len] = p->envp[len];
		len++;
	}
	new[len++] = ft_strdup(to_add);
	new[len] = NULL;
	ft_memdel((void **)&(p->envp));
	p->envp = new;
}

static void		add_process_and_msg_cmd(t_ast *ast, t_job *j)
{
	if (!ast)
		return ;
	if (ast->left)
		add_process_and_msg_cmd(ast->left, j);
	if (!(j->command))
		j->command = ft_strdup(ast->token->lexeme);
	else if (ast->token->tokind != T_EOF && !(j->command = arg_join(\
					j->command, " ", ast->token->lexeme)))
		to_exit(ER_MALLOC);
	if (g_is_pipe == true)
		push_back_process(&(j->first_process), g_shell.envp);
	if (is_redir_exec(ast->token->tokind))
		g_redir_tab[ast->token->tokind](ast, j);
	if (ast->token->tokind == T_WORD)
		realloc_argv(&(j->first_process), ast->token->lexeme);
	if (ast->token->tokind == T_ASGMT_WRD)
		realloc_assign(&(j->first_process), ast->token->lexeme);
	g_is_pipe = (ast->token->tokind != T_PIPE) ? false : true;
	if (ast->right && !is_redir_exec(ast->token->tokind))
		add_process_and_msg_cmd(ast->right, j);
}

void			push_back_job(t_ast *ast)
{
	t_job	*new;
	t_job	*j;

	if (!(new = (t_job *)ft_memalloc(sizeof(t_job))))
		to_exit(ER_MALLOC);
	if (!(j = last_job()))
		g_shell.first_job = new;
	g_is_pipe = true;
	new->stdin = STDIN_FILENO;
	new->stdout = STDOUT_FILENO;
	new->stderr = STDERR_FILENO;
	add_process_and_msg_cmd(ast, new);
	if (j != NULL)
		j->next = new;
	new->id = create_job_id(1);
}

void			remove_completed_job(t_job **job)
{
	t_job *prev;
	t_job *curr;
	t_job *next;

	if (!job || !(curr = *job))
		return ;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		if (job_is_completed(curr) && !curr->started_in_bg)
		{
			free_job(curr);
			if (prev)
				prev->next = next;
			else
				(*job) = next;
		}
		else
			prev = curr;
		curr = next;
	}
}
