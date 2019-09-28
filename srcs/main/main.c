/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:16:46 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 09:21:07 by araout           ###   ########.fr       */
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
}

int		main(int ac, char **av, char **envp)
{
	t_edit	*line_e;

	(void)av;
	(void)ac;
	line_e = st_line();
	init_term(line_e, envp);
	while (1)
	{
		line_edit(line_e);
		replace_aliases(line_e);
		ft_printf("[%s]\n", line_e->line);
		remove_duplicate_whitespaces(line_e);
		line_parser(line_e);
		line_execution();
		if (g_shell.isnt_interactive == 1)
			g_shell.isnt_interactive = 0;
		else
			write_history(line_e->line);
	}
	return (fexit(0));
}
