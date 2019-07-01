/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:16:46 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 12:00:48 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int main(int ac, char **av, char **envp)
{
	t_edit *line_e;

	(void)av;
	(void)ac;
	line_e = st_line();
	set_terminal(line_e, envp);
	//ft_signal_handle();
	while (1)
	{
		init_line(line_e);
		while (!line_e->line)
		{
				line_e->prompt_size = print_prompt(0);
				line_edition(line_e);
		}
		//line_lexer(line_e);
	//	execution();
		if (line_e->line && !ft_strcmp(line_e->line, "reset"))//buitin
			tputs(tgetstr("cl", NULL), 1, ft_puti);
		if (line_e->line && !ft_strcmp(line_e->line, "exit"))//buitin
			break ;//to rm
	//	ft_putendl("");//to make after command exec
	}
	ft_strdel(&(line_e->line));
	if (tcsetattr(STDERR_FILENO, TCSADRAIN, line_e->termiold) == -1)
		toexit(0, "tcsetattr", 1);
	return (0);
}
