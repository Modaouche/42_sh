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

static bool is_pipe;

t_job		*last_job(void)
{
	t_job		*j;

	j = g_shell.first_job;
	while (j && j->next)
		j = j->next;
	return (j);
}

void			push_back_process(t_process **p)
{
	t_process	*new;

	ft_printf("push process\n");
	if (!(new = (t_process *)ft_memalloc(sizeof(t_process))))
		to_exit(ER_MALLOC);
	while (*p)
		*p = (*p)->next;
	*p = new;
}

static void		realloc_argv(t_process **process, char *to_add)
{
	char		**new;
	int 		len;
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
       	new[len++] = ft_strdup(to_add);
       	new[len] = NULL;
	ft_memdel((void **)&(p->argv));
	p->argv = new;
	len = 0;//test<< VV
	ft_putstr("realloc_argv for process ->");
	while (p->argv[len])
		ft_printf("[%s]  ", p->argv[len++]);
	ft_putendl("");
}

static void		add_process_and_msg_cmd(t_ast *ast, t_job *j)
{
	if (!ast)
		return ;
	if (ast->left)
		add_process_and_msg_cmd(ast->left, j);
	if (!(j->command))
		j->command = ft_strdup(ast->token->lexeme);
	else if (!(j->command = ft_multijoin(3, j->command, " ",\
			ast->token->lexeme)))
		to_exit(ER_MALLOC);
	if (is_pipe == true)
		push_back_process(&(j->first_process));
	if (ast->token->tokind == T_WORD)
		realloc_argv(&(j->first_process), ast->token->lexeme);
	is_pipe = (ast->token->tokind != T_PIPE) ? false : true;
	if (ast->right)
		add_process_and_msg_cmd(ast->right, j);
}

void		push_back_job(t_ast *ast)
{
	t_job	*new;
	t_job	*j;

	if (!(new = (t_job *)ft_memalloc(sizeof(t_job))))
		to_exit(ER_MALLOC);
	if (!(j = last_job()))
		g_shell.first_job = new;
	is_pipe = true;
	add_process_and_msg_cmd(ast, new);
	if (!j)
		j = new;
	else
		j->next = new;
	new->stdout = STDOUT_FILENO;
	new->stderr = STDERR_FILENO;

	ft_printf("test job command message -> %s\n", new->command);
}

