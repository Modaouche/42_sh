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

int main(int ac, char **av, char **envp)
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
		line_execution();
		if (line_e->line && !ft_strcmp(line_e->line, "clear"))//buitin
			tputs(tgetstr("cl", NULL), 1, ft_puti);
		if (line_e->line && !ft_strcmp(line_e->line, "exit"))//buitin
			break ;
	}
	//un free de tout donc les ligne ci dessous sont a virer
	ft_strdel(&(line_e->line));//a virer car il y aura un grand nettoyage
	if (tcsetattr(STDERR_FILENO, TCSADRAIN, g_shell.termiold) == -1)
		le_exit(0);//idem
	return (0);
}
