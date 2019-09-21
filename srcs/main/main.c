/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:16:46 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/21 01:51:38 by mgheraie         ###   ########.fr       */
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

	(void)av;//we might add possibility to use '.sh' file
	(void)ac;
	line_e = st_line();
	init_term(line_e, envp);
	while (1)
	{
		line_edit(line_e);

		//char *res = param_expansion(line_e->line);
		//ft_printf("RESULT = [%s]\n",res);
		//ft_strdel(&res);

		replace_aliases(line_e);
		line_parser(line_e);
		line_execution();
		if (g_shell.isnt_interactive == 1)
			g_shell.isnt_interactive = 0;
		else
			write_history(line_e->line);
	}
	//free et exit dan fonction fexit OK !
	//un free de tout donc les ligne ci dessous sont a virer
	if (tcsetattr(STDERR_FILENO, TCSADRAIN, g_shell.termiold) == -1)
	        le_exit(0);//idem
	return (0);
}

