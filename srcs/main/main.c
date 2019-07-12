/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:16:46 by modaouch          #+#    #+#             */
/*   Updated: 2019/07/10 06:20:04 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	line_edit(t_edit *line_e)
{
	init_line(line_e);
	signal_handler(LINE_EDIT);
	while (!line_e->line)
	{
		g_shell.prompt_size = print_prompt(0);
		line_edition(line_e);
	}
	signal_handler(REGULAR);
}//cree une fonction generique (tu as le meme genre de code dans le parser)

int		main(int ac, char **av, char **envp)
{
	t_edit	*line_e;

	(void)av;//to init in g_shell with set_term fct
	(void)ac;//to init in g_shell with set_term fct
	line_e = st_line();
	init_term(line_e, envp);
	while (1)
	{
		line_edit(line_e);
		line_parser(line_e);
		g_shell.line_e = line_e;
		write_history(line_e->line);
		ft_built_in(line_e->line);
		line_execution();
	//	ft_putendl("");//to make after command exec
	}
	//free et exit dan fonction fexit OK !
	//un free de tout donc les ligne ci dessous sont a virer
	//aussis g_shell.envp a free
	fexit(NULL);
	return (0);
}
