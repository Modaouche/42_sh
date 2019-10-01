/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 22:00:43 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 09:02:29 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "job.h"

t_token	*ast_get_lexeme(t_ast *ast)
{
	ast = ast->right;
	while (ast && ast->left)
		ast = ast->left;
	return (ast->token);
}

void	handle_err_fd(t_job *j, int io_nb, int fd)
{
	if (io_nb == 2)
	{
		if (j->stderr != STDERR_FILENO)
		{
			ft_printf("2 close = %d\n", j->stderr);
			close(j->stderr);
		}
		ft_printf("2 = %d\n", fd);
		j->stderr = fd;
	}
}

void	check_opened_fd(t_job *j, int io_nb, int fd)
{
	if (io_nb == 0)
	{
		ft_printf("0 = %d\n", fd);
		if (j->stdin != STDIN_FILENO)
		{
			ft_printf("0 close = %d\n", j->stdout);
			close(j->stdin);
		}
		j->stdin = fd;
	}
	if (io_nb == 1)
	{
		if (j->stdout != STDOUT_FILENO)
		{
			ft_printf("1 close = %d\n", j->stdout);
			close(j->stdout);
		}
		ft_printf("1 = %d\n", fd);
		j->stdout = fd;
	}
	handle_err_fd(j, io_nb, fd);
}

int		get_redir_fd(char *lex, int check)
{
	int			i;
	struct stat	tmp;

	i = 0;
	while (lex && ft_isdigit(lex[i]))
		i++;
	if ((fstat(ft_atoi(lex), &tmp) == -1))
		return (-1);
	else if (check == 0 && (read(ft_atoi(lex), "", 0) != -1))
		return (-1);
	else if (check == 1 && (write(ft_atoi(lex), "", 0) != -1))
		return (-1);
	if (!lex[i] || (lex[i] == '-' && !lex[i + 1]))
		return (ft_atoi(lex));
	return (-1);
}
