/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:16:46 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 02:48:43 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int		init_term(void)
{
	char		*term_type;
	int			ret;

	if (!(term_type = getenv("TERM")))
		return (-1);
	ret = tgetent(NULL, getenv("TERM"));
	if (ret == 1 && ft_strcmp("dumb", getenv("TERM")))
		return (0);
	g_errorno = (ret > 0 && ft_strcmp("dumb", getenv("TERM")))
    	? ER_DBACCES : ER_DBINFO;
	return (-1);
}

int main(int ac, char **av, char **envp)
{
	t_edit line_e;

	(void)av;
	(void)ac;
	ft_bzero(&line_e, sizeof(line_e));
	line_e.env = envp;
	line_e.tc_onoff = (init_term() == -1) ? 1 : 0;//ici set off l'utilisation des termcaps
	set_terminal(&line_e);
	fill_token_tab();
	//ft_signal_handle();
	while (1)
	{
		// line_e.len_/max = BUFFER_LEN;
		// line_e.cursor_pos = 0;
		// line_e.len = 0;
		init_line(&line_e);
		while (!line_e.line)
		{
				line_e.prompt_size = print_prompt(0);
				line_edition(&line_e);
		}
		line_lexer(&line_e);
		//execution de commande...
		if (line_e.line && !ft_strcmp(line_e.line, "reset"))//buitin
			tputs(tgetstr("cl", NULL), 1, ft_puti);
		if (line_e.line && !ft_strcmp(line_e.line, "exit"))//buitin
			break ;//to rm
		ft_putendl("");
	}
	ft_strdel(&(line_e.line));
	if (tcsetattr(STDERR_FILENO, TCSADRAIN, line_e.termiold) == -1)
		toexit(0, "tcsetattr");
    return (0);
}
